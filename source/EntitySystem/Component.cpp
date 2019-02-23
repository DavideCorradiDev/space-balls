#include <EntitySystem/Component.hpp>
#include <EntitySystem/Entity.hpp>
#include <MessageSystem/MsgPoseDisplacement.hpp>
#include <MessageSystem/MsgSetPose.hpp>
#include <cassert>

namespace mnk {

Component::Component() :
    GameObject(),
    mpEntity(nullptr) {
    addCallback<MsgSetPose>([this](const MsgSetPose& message) {
        setPosition(message.position);
        setRotation(message.orientationDeg);
    });
    addCallback<MsgPoseDisplacement>([this](const MsgPoseDisplacement& message) {
        move(message.translation);
        rotate(message.rotationDeg);
    });
}

Component::~Component() {
    if(mpEntity) removeComponentFromEntity(*this, *mpEntity);
}

Entity* Component::getpEntity() const { return mpEntity; }
void Component::setpEntity(Entity* pEntity) { mpEntity = pEntity; }
void Component::sendMessageToEntity(const Message& message) const {
    if(mpEntity) mpEntity->handleMessage(message);
}

}
