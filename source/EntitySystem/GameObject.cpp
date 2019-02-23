#include <EntitySystem/GameObject.hpp>
#include <MessageSystem/MsgChangeStatus.hpp>
#include <EntitySystem/GameSystemBase.hpp>
#include <cassert>

namespace mnk {

GameObject::GameObject() :
    mStatus(Status::SetForActivation),
    mpSystem(nullptr) {
    addCallback<MsgChangeStatus>([this](const MsgChangeStatus& message) {
        mStatus = message.status;
    });
}

GameObject::~GameObject() {}

bool GameObject::isSetForActivation() const { return mStatus == Status::SetForActivation; }
bool GameObject::isActive() const { return mStatus == Status::Active; }
void GameObject::setActive() {
    mStatus = Status::Active;
    onActivation();
}
bool GameObject::isDeleted() const { return mStatus == Status::Deleted; }
void GameObject::setDeleted() { mStatus = Status::Deleted; }

GameSystemBase* GameObject::getpSystem() const { return mpSystem; }
void GameObject::setpSystem(GameSystemBase* pSystem) { mpSystem = pSystem; }
void GameObject::sendMessageToSystem(const Message& message) const {
    if(mpSystem) mpSystem->handleMessage(message);
}

void GameObject::onActivation() {}

}
