#include <PhysicsSystem/PhysicsComponent.hpp>
#include <MessageSystem/MsgPoseDisplacement.hpp>
#include <cassert>

namespace mnk {

PhysicsComponent::PhysicsComponent() :
    mpContactShape(nullptr) {
    setCallbacks();
}

PhysicsComponent::PhysicsComponent(std::unique_ptr<ContactShape> pContactShape) :
    mpContactShape(std::move(pContactShape)) {
    setCallbacks();
}

PhysicsComponent::~PhysicsComponent() {}

void PhysicsComponent::update(sf::Time dt) {}

const ContactShape* PhysicsComponent::getpContactShape() const { return mpContactShape.get(); }
void PhysicsComponent::setpContactShape(std::unique_ptr<ContactShape> pContactShape) { mpContactShape = std::move(pContactShape); }

void PhysicsComponent::setCallbacks() {
    removeCallback<MsgPoseDisplacement>();
    addCallback<MsgPoseDisplacement>([this](const MsgPoseDisplacement& message) {
        move(message.translation);
        rotate(message.rotationDeg);
        assert(mpContactShape);
        mpContactShape->move(message.translation);
        mpContactShape->rotate(message.rotationDeg);
    });
}

ContactInformation checkContact(const PhysicsComponent& component1, const PhysicsComponent& component2) {
    if(component1.getpContactShape() && component2.getpContactShape()) {
        return checkContact(*(component1.getpContactShape()), *(component2.getpContactShape()));
    }
    return ContactInformation(false);
}

}
