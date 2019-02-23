#include <GameplaySystem/GCUfo.hpp>
#include <EntitySystem/EntityFactory.hpp>
#include <MessageSystem/MsgContact.hpp>
#include <MessageSystem/MsgContactBullet.hpp>
#include <MessageSystem/MsgContactShip.hpp>
#include <MessageSystem/MsgContactSpaceBall.hpp>
#include <MessageSystem/MsgShipPosition.hpp>
#include <MessageSystem/MsgPlaySound.hpp>
#include <MessageSystem/MsgChangeStatus.hpp>
#include <MessageSystem/MsgPoseDisplacement.hpp>
#include <MessageSystem/MsgUfoDestroyed.hpp>
#include <EntitySystem/EDExplosion.hpp>
#include <Utilities/UtilityMethods.hpp>

namespace mnk {

GCUfo::GCUfo(EntityFactory& entityFactory, float speed, float reloadTime, float bulletSpeed, EDUfo::Type type) :
    mEntityFactory(entityFactory),
    mSpeed(speed),
    mReloadTime(reloadTime),
    mTimeSinceLastAttack(0.f),
    mBulletSpeed(bulletSpeed),
    mShipPosition(),
    mType(type) {

    addCallback<MsgShipPosition>([this](const MsgShipPosition& message) {
        mShipPosition = message.position;
    });

    addCallback<MsgContact>([this](const MsgContact& message) {
        message.otherEntity.handleMessage(MsgContactShip(false));
    });

    addCallback<MsgContactSpaceBall>([this](const MsgContactSpaceBall& message) {
        destroy();
    });

    addCallback<MsgContactBullet>([this](const MsgContactBullet& message) {
        if(message.ofPlayer) {
            destroy();
        }
    });

    addCallback<MsgContactShip>([this](const MsgContactShip& message) {
        destroy();
    });
}

GCUfo::~GCUfo() {}

void GCUfo::update(sf::Time dt) {
    performMovement(dt);
    mTimeSinceLastAttack += dt.asSeconds();
    if(mTimeSinceLastAttack >= mReloadTime) {
        mTimeSinceLastAttack -= mReloadTime;
        attack();
    }
}

void GCUfo::destroy() {
    sendMessageToEntity(MsgChangeStatus(Status::Deleted));
    sendMessageToEntity(MsgPlaySound(SoundBufferId::Explosion));
    mEntityFactory.createEntity(EDExplosion(), getPosition());
    sendMessageToSystem(MsgUfoDestroyed(mType));
}

}
