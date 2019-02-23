#include <GameplaySystem/GCBullet.hpp>
#include <MessageSystem/MsgChangeStatus.hpp>
#include <MessageSystem/MsgContact.hpp>
#include <MessageSystem/MsgContactBullet.hpp>
#include <MessageSystem/MsgContactShip.hpp>
#include <MessageSystem/MsgContactSpaceBall.hpp>
#include <MessageSystem/MsgNewLevel.hpp>
#include <EntitySystem/Entity.hpp>
#include <EntitySystem/EDExplosion.hpp>
#include <EntitySystem/EntityFactory.hpp>

namespace mnk {

GCBullet::GCBullet(EntityFactory& entityFactory, float lifeTime, bool ofPlayer) :
    mEntityFactory(entityFactory),
    mLifeTime(lifeTime),
    mOfPlayer(ofPlayer) {
    addCallback<MsgContact>([this](const MsgContact& message) {
        message.otherEntity.handleMessage(MsgContactBullet(mOfPlayer));
    });
    addCallback<MsgContactShip>([this](const MsgContactShip& message) {
        if((mOfPlayer && !message.isPlayer) || (!mOfPlayer && message.isPlayer)) {
            sendMessageToEntity(MsgChangeStatus(Status::Deleted));
        }
    });
    addCallback<MsgContactSpaceBall>([this] (const MsgContactSpaceBall) {
        sendMessageToEntity(MsgChangeStatus(Status::Deleted));
        mEntityFactory.createEntity(EDExplosion(), getPosition());
    });
    addCallback<MsgNewLevel>([this](const MsgNewLevel& message) {
        sendMessageToEntity(MsgChangeStatus(Status::Deleted));
    });
}

GCBullet::~GCBullet() {}

void GCBullet::update(sf::Time dt) {
    mLifeTime -= dt.asSeconds();
    if(mLifeTime <= 0) {
        sendMessageToEntity(MsgChangeStatus(Status::Deleted));
    }
}

}
