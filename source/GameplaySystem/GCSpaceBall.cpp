#include <GameplaySystem/GCSpaceBall.hpp>
#include <MessageSystem/MsgChangeStatus.hpp>
#include <MessageSystem/MsgContact.hpp>
#include <MessageSystem/MsgContactBullet.hpp>
#include <MessageSystem/MsgContactShip.hpp>
#include <MessageSystem/MsgContactSpaceBall.hpp>
#include <MessageSystem/MsgSpaceBallDestroyed.hpp>
#include <MessageSystem/MsgSpaceBallCreated.hpp>
#include <EntitySystem/Entity.hpp>
#include <EntitySystem/EntityFactory.hpp>
#include <Utilities/Randomizer.hpp>
#include <Utilities/UtilityMethods.hpp>

namespace mnk {

GCSpaceBall::GCSpaceBall(EntityFactory& entityFactory, EDSpaceBall::Size size) :
    mEntityFactory(entityFactory),
    mSize(size) {
    addCallback<MsgContact>([this](const MsgContact& message) {
        message.otherEntity.handleMessage(MsgContactSpaceBall());
    });
    addCallback<MsgContactBullet>([this](const MsgContactBullet& message) {
        destroy();
    });
    addCallback<MsgContactShip>([this](const MsgContactShip& message) {
        destroy();
    });
}

GCSpaceBall::~GCSpaceBall() {}

void GCSpaceBall::destroy() {
    sendMessageToEntity(MsgChangeStatus(Status::Deleted));
    sendMessageToSystem(MsgSpaceBallDestroyed(mSize));
    float creationAngle = Randomizer::random(0.0f, 180.0f);
    switch(mSize) {
    case EDSpaceBall::Size::Big:
        mEntityFactory.createEntity(EDSpaceBall(EDSpaceBall::Size::Medium, getOrientationVector(Randomizer::random(0.0f,360.0f))),
                                    getPosition() + 16.0f * getOrientationVector(creationAngle));
        mEntityFactory.createEntity(EDSpaceBall(EDSpaceBall::Size::Medium, getOrientationVector(Randomizer::random(0.0f,360.0f))),
                                    getPosition() + 16.0f * getOrientationVector(creationAngle + 180.0f));
        sendMessageToSystem(MsgSpaceBallCreated());
        sendMessageToSystem(MsgSpaceBallCreated());
        break;
    case EDSpaceBall::Size::Medium:
        mEntityFactory.createEntity(EDSpaceBall(EDSpaceBall::Size::Small, getOrientationVector(Randomizer::random(0.0f,360.0f))),
                                    getPosition() + 8.0f * getOrientationVector(creationAngle));
        mEntityFactory.createEntity(EDSpaceBall(EDSpaceBall::Size::Small, getOrientationVector(Randomizer::random(0.0f,360.0f))),
                                    getPosition() + 8.0f * getOrientationVector(creationAngle + 180.0f));
        sendMessageToSystem(MsgSpaceBallCreated());
        sendMessageToSystem(MsgSpaceBallCreated());
        break;
    default:
        break;
    }
}

}
