#include <EntitySystem/EntityFactory.hpp>

#include <MessageSystem/MsgPoseDisplacement.hpp>

#include <ResourceSystem/Resources.hpp>

#include <EntitySystem/EntitySystem.hpp>
#include <EntitySystem/EDBullet.hpp>
#include <EntitySystem/EDShip.hpp>
#include <EntitySystem/EDSpaceBall.hpp>
#include <EntitySystem/EDSpawner.hpp>
#include <EntitySystem/EDExplosion.hpp>
#include <EntitySystem/EDStaticPicture.hpp>
#include <EntitySystem/EDUfo.hpp>

#include <GameplaySystem/GameplaySystem.hpp>
#include <GameplaySystem/GCBullet.hpp>
#include <GameplaySystem/GCShip.hpp>
#include <GameplaySystem/GCSpaceBall.hpp>
#include <GameplaySystem/GCSpawner.hpp>
#include <GameplaySystem/GCTimedLife.hpp>
#include <GameplaySystem/GCDumbUfo.hpp>
#include <GameplaySystem/GCSmartUfo.hpp>

#include <InputSystem/InputSystem.hpp>
#include <InputSystem/ICPlayerShip.hpp>

#include <PhysicsSystem/PhysicsSystem.hpp>
#include <PhysicsSystem/PCKinematicBody.hpp>
#include <PhysicsSystem/CSAxisAlignedRectangle.hpp>
#include <PhysicsSystem/CSCircle.hpp>

#include <AudioSystem/AudioSystem.hpp>
#include <AudioSystem/ACSoundPlayer.hpp>
#include <AudioSystem/ACSoundEmitter.hpp>

#include <RenderSystem/RenderSystem.hpp>
#include <RenderSystem/RCAnimatedSprite.hpp>
#include <RenderSystem/RCShape.hpp>
#include <RenderSystem/RCSprite.hpp>
#include <RenderSystem/RCGui.hpp>

#include <Utilities/UtilityMethods.hpp>

#include <MessageSystem/MsgCmdAccelerate.hpp>
#include <MessageSystem/MsgCmdStop.hpp>
#include <MessageSystem/MsgPlaySound.hpp>

namespace mnk {

EntityFactory::EntityFactory(const Resources& resources, EntitySystem& entitySystem, GameplaySystem& gameplaySystem, InputSystem& inputSystem, PhysicsSystem& physicsSystem, AudioSystem& audioSystem, RenderSystem& renderSystem) :
    mResources(resources),
    mEntitySystem(entitySystem),
    mGameplaySystem(gameplaySystem),
    mInputSystem(inputSystem),
    mPhysicsSystem(physicsSystem),
    mAudioSystem(audioSystem),
    mRenderSystem(renderSystem) {
    initializeFactoryFunctionsMap();
}

Entity* EntityFactory::createEntity(const EntityData& data, const sf::Vector2f& position, float orientationDeg) {
    Entity* entity = mFactoryFunctions[std::type_index(typeid(data))](data);
    entity->handleMessage(MsgPoseDisplacement(position, orientationDeg));
    return entity;
}

void EntityFactory::initializeFactoryFunctionsMap() {
    addFactoryFunction<EDBullet>([this](const EDBullet& data) {
        Entity* pEntity = new Entity();
        mEntitySystem.addObject(std::unique_ptr<Entity>(pEntity));

        // Set lifetime so that the bullet has a range equal to 400 pixels.
        std::unique_ptr<GCBullet> pGCBullet(new GCBullet(*this, 400.0f / norm(data.velocity), data.ofPlayer));
        addComponentToEntity(*pGCBullet, *pEntity);
        mGameplaySystem.addObject(std::move(pGCBullet));

        std::unique_ptr<PCKinematicBody> pPCKinBody(new PCKinematicBody(std::unique_ptr<CSCircle>(new CSCircle(2))));
        pPCKinBody->setLinearVelocity(data.velocity);
        addComponentToEntity(*pPCKinBody, *pEntity);
        mPhysicsSystem.addObject(std::move(pPCKinBody));

        std::unique_ptr<RCSprite> pRCSprite(new RCSprite(mResources.textureHolder.get(TextureId::Bullet)));
        addComponentToEntity(*pRCSprite, *pEntity);
        mRenderSystem.addObject(std::move(pRCSprite));

//        std::unique_ptr<sf::CircleShape> pCircle(new sf::CircleShape(2));
//        pCircle->setFillColor(sf::Color::Transparent);
//        pCircle->setOutlineColor(sf::Color::White);
//        pCircle->setOutlineThickness(1);
//        centerOrigin(*pCircle);
//        std::unique_ptr<RCShape> pRCShape(new RCShape(std::move(pCircle)));
//        addComponentToEntity(*pRCShape, *pEntity);
//        mRenderSystem.addObject(std::move(pRCShape));

        return pEntity;
    });

    addFactoryFunction<EDShip>([this](const EDShip& data) {
        Entity* pEntity = new Entity();
        mEntitySystem.addObject(std::unique_ptr<Entity>(pEntity));

        RCAnimatedSprite* pRCAnimatedSprite = new RCAnimatedSprite(mResources.animationHolder.get(AnimationId::Ship), sf::seconds(0.25f));
        pRCAnimatedSprite->getAnimatedSprite().pause();
        pRCAnimatedSprite->addCallback<MsgCmdAccelerate>([pRCAnimatedSprite](const MsgCmdAccelerate& message) {
            pRCAnimatedSprite->getAnimatedSprite().increaseCurrentFrame();
            pRCAnimatedSprite->getAnimatedSprite().play();
        });
        pRCAnimatedSprite->addCallback<MsgCmdStop>([pRCAnimatedSprite](const MsgCmdStop& message) {
            pRCAnimatedSprite->getAnimatedSprite().pause();
            pRCAnimatedSprite->getAnimatedSprite().restart();
        });
        addComponentToEntity(*pRCAnimatedSprite, *pEntity);
        mRenderSystem.addObject(std::unique_ptr<RenderComponent>(pRCAnimatedSprite));

        std::unique_ptr<GCShip> pGCShip(new GCShip(*this, data.turnSpeed, data.acceleration, data.reloadTime, data.bulletSpeed, data.contactRadius + 1, data.invulnerabilityTime));
        addComponentToEntity(*pGCShip, *pEntity);
        mGameplaySystem.addObject(std::move(pGCShip));

        std::unique_ptr<ICPlayerShip> pICPlayerShip(new ICPlayerShip());
        addComponentToEntity(*pICPlayerShip, *pEntity);
        mInputSystem.addObject(std::move(pICPlayerShip));

        std::unique_ptr<PCKinematicBody> pPCKinBody(new PCKinematicBody(std::unique_ptr<CSCircle>(new CSCircle(data.contactRadius))));
        pPCKinBody->setLinearVelocityLimit(sf::Vector2f(300.0f, 300.0f));
        pPCKinBody->setSolid(false);
        addComponentToEntity(*pPCKinBody, *pEntity);
        mPhysicsSystem.addObject(std::move(pPCKinBody));

        std::unique_ptr<ACSoundPlayer> pAudio(new ACSoundPlayer(mResources.soundBufferHolder));
        addComponentToEntity(*pAudio, *pEntity);
        mAudioSystem.addObject(std::move(pAudio));

        ACSoundEmitter* pEngineSound = new ACSoundEmitter(mResources.soundBufferHolder.get(SoundBufferId::Engine));
        pEngineSound->getSound().setLoop(true);
        pEngineSound->addCallback<MsgCmdAccelerate>([pEngineSound](const MsgCmdAccelerate& message) {
            pEngineSound->getSound().play();
        });
        pEngineSound->addCallback<MsgCmdStop>([pEngineSound](const MsgCmdStop& message) {
            pEngineSound->getSound().stop();
        });
        addComponentToEntity(*pEngineSound, *pEntity);
        mAudioSystem.addObject(std::unique_ptr<AudioComponent>(pEngineSound));

//        std::unique_ptr<sf::CircleShape> pCircle(new sf::CircleShape(data.contactRadius));
//        pCircle->setFillColor(sf::Color::Transparent);
//        pCircle->setOutlineColor(sf::Color::White);
//        pCircle->setOutlineThickness(1);
//        centerOrigin(*pCircle);
//        std::unique_ptr<RCShape> pRCShape(new RCShape(std::move(pCircle)));
//        addComponentToEntity(*pRCShape, *pEntity);
//        mRenderSystem.addObject(std::move(pRCShape));

        return pEntity;
    });

    addFactoryFunction<EDSpaceBall>([this](const EDSpaceBall& data) {
        Entity* pEntity = new Entity();
        mEntitySystem.addObject(std::unique_ptr<Entity>(pEntity));

        float contactRadius = 0.0f;
        float speed = 0.0f;
        float scale = 0.0f;
        float mass = 0.0f;
        switch(data.size) {
        case EDSpaceBall::Size::Big:
            contactRadius = 32.0f;
            speed = 32.0f;
            scale = 1.0f;
            mass = 2.0f;
            break;
        case EDSpaceBall::Size::Medium:
            contactRadius = 16.0f;
            speed = 64.0f;
            scale = 0.5f;
            mass = 1.0f;
            break;
        case EDSpaceBall::Size::Small:
            contactRadius = 8.0f;
            speed = 128.0f;
            scale = 0.25f;
            mass = 0.5f;
            break;
        }

        std::unique_ptr<GCSpaceBall> pGCSpaceBall(new GCSpaceBall(*this, data.size));
        addComponentToEntity(*pGCSpaceBall, *pEntity);
        mGameplaySystem.addObject(std::move(pGCSpaceBall));

        std::unique_ptr<PCKinematicBody> pPCKinBody(new PCKinematicBody(std::unique_ptr<CSCircle>(new CSCircle(contactRadius))));
        pPCKinBody->setMass(mass);
        pPCKinBody->setLinearVelocity(data.moveDirection * speed);
        addComponentToEntity(*pPCKinBody, *pEntity);
        mPhysicsSystem.addObject(std::move(pPCKinBody));

        std::unique_ptr<ACSoundPlayer> pAudio(new ACSoundPlayer(mResources.soundBufferHolder));
        addComponentToEntity(*pAudio, *pEntity);
        mAudioSystem.addObject(std::move(pAudio));

        std::unique_ptr<RCSprite> pRCSprite(new RCSprite(mResources.textureHolder.get(TextureId::SpaceBall)));
        pRCSprite->getSprite().setScale(scale, scale);
        addComponentToEntity(*pRCSprite, *pEntity);
        mRenderSystem.addObject(std::move(pRCSprite));

        return pEntity;
    });

    addFactoryFunction<EDSpawner>([this](const EDSpawner& data) {
        Entity* pEntity = new Entity();
        mEntitySystem.addObject(std::unique_ptr<Entity>(pEntity));

        std::unique_ptr<GCSpawner> pGCSpawner(new GCSpawner(*this, data.worldSize));
        addComponentToEntity(*pGCSpawner, *pEntity);
        mGameplaySystem.addObject(std::move(pGCSpawner));

        ACSoundPlayer* pAudio(new ACSoundPlayer(mResources.soundBufferHolder));
        addComponentToEntity(*pAudio, *pEntity);
        mAudioSystem.addObject(std::unique_ptr<AudioComponent>(pAudio));

        return pEntity;
    });

    addFactoryFunction<EDExplosion>([this](const EDExplosion& data) {
        Entity* pEntity = new Entity();
        mEntitySystem.addObject(std::unique_ptr<Entity>(pEntity));

        float frameTime = 0.05f;
        RCAnimatedSprite* pRCSprite = new RCAnimatedSprite(mResources.animationHolder.get(AnimationId::Explosion), sf::seconds(frameTime));
        addComponentToEntity(*pRCSprite, *pEntity);
        mRenderSystem.addObject(std::unique_ptr<RenderComponent>(pRCSprite));

        GCTimedLife* pGCTimedLife = new GCTimedLife(sf::seconds(frameTime * static_cast<float>(pRCSprite->getAnimatedSprite().getAnimation()->getNumberOfFrames())));
        addComponentToEntity(*pGCTimedLife, *pEntity);
        mGameplaySystem.addObject(std::unique_ptr<GameplayComponent>(pGCTimedLife));

        ACSoundPlayer* pACAudio = new ACSoundPlayer(mResources.soundBufferHolder);
        pACAudio->handleMessage(MsgPlaySound(SoundBufferId::Explosion));
        addComponentToEntity(*pACAudio, *pEntity);
        mAudioSystem.addObject(std::unique_ptr<AudioComponent>(pACAudio));

        return pEntity;
    });

    addFactoryFunction<EDStaticPicture>([this](const EDStaticPicture& data) {
        Entity* pEntity = new Entity();
        mEntitySystem.addObject(std::unique_ptr<Entity>(pEntity));

        RCSprite* pRCSprite = new RCSprite(mResources.textureHolder.get(data.textureId));
        addComponentToEntity(*pRCSprite, *pEntity);
        mRenderSystem.addObject(std::unique_ptr<RenderComponent>(pRCSprite));

        return pEntity;
    });

    addFactoryFunction<EDUfo>([this](const EDUfo& data) {
        Entity* pEntity = new Entity();
        mEntitySystem.addObject(std::unique_ptr<Entity>(pEntity));

        float contactRadius = 0.0f;
        float speed = 0.0f;
        float scale = 0.0f;
        float reloadTime = 0.0f;
        float bulletSpeed = 0.0f;
        float shootDeviation = 30.f;
        std::unique_ptr<GCUfo> pGCUfo;
        switch(data.type) {
        case EDUfo::Type::Dumb:
            contactRadius = 16.f;
            speed = 64.f;
            scale = 1.0f;
            reloadTime = 1.5f;
            bulletSpeed = 600.f;
            pGCUfo = std::unique_ptr<GCUfo>(new GCDumbUfo(*this, speed, reloadTime, bulletSpeed, data.type));
            addComponentToEntity(*pGCUfo, *pEntity);
            mGameplaySystem.addObject(std::move(pGCUfo));
            break;
        case EDUfo::Type::Smart:
            contactRadius = 8.f;
            speed = 64.f;
            scale = 0.5f;
            reloadTime = 1.5f;
            bulletSpeed = 600.f;
            pGCUfo = std::unique_ptr<GCUfo>(new GCSmartUfo(*this, speed, reloadTime, bulletSpeed, data.type, shootDeviation));
            addComponentToEntity(*pGCUfo, *pEntity);
            mGameplaySystem.addObject(std::move(pGCUfo));
            break;
        }

        std::unique_ptr<PCKinematicBody> pPCKinBody(new PCKinematicBody(std::unique_ptr<CSCircle>(new CSCircle(contactRadius))));
        pPCKinBody->setLinearVelocityLimit(sf::Vector2f(300.0f, 300.0f));
        pPCKinBody->setSolid(false);
        addComponentToEntity(*pPCKinBody, *pEntity);
        mPhysicsSystem.addObject(std::move(pPCKinBody));

        std::unique_ptr<ACSoundPlayer> pAudio(new ACSoundPlayer(mResources.soundBufferHolder));
        addComponentToEntity(*pAudio, *pEntity);
        mAudioSystem.addObject(std::move(pAudio));

        ACSoundEmitter* pEngineSound = new ACSoundEmitter(mResources.soundBufferHolder.get(SoundBufferId::Ufo));
        pEngineSound->getSound().setLoop(true);
        pEngineSound->getSound().play();
        addComponentToEntity(*pEngineSound, *pEntity);
        mAudioSystem.addObject(std::unique_ptr<AudioComponent>(pEngineSound));

        std::unique_ptr<RCSprite> pRCSprite(new RCSprite(mResources.textureHolder.get(TextureId::Ufo)));
        pRCSprite->getSprite().setScale(scale, scale);
        addComponentToEntity(*pRCSprite, *pEntity);
        mRenderSystem.addObject(std::move(pRCSprite));

        return pEntity;
    });
}

}
