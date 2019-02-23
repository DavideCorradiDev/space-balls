#include <GameplaySystem/GCTimedLife.hpp>
#include <MessageSystem/MsgChangeStatus.hpp>

namespace mnk {

GCTimedLife::GCTimedLife(sf::Time lifeTime) :
    mLifeTime(lifeTime),
    mCurrentTime(sf::seconds(0.0f)) {}

GCTimedLife::~GCTimedLife() {}

void GCTimedLife::update(sf::Time dt) {
    mCurrentTime += dt;
    if(mCurrentTime >= mLifeTime) {
        sendMessageToEntity(MsgChangeStatus(Status::Deleted));
    }
}

}
