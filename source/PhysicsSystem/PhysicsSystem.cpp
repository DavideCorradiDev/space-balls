#include <PhysicsSystem/PhysicsSystem.hpp>
#include <MessageSystem/MsgContact.hpp>
#include <MessageSystem/MsgPoseDisplacement.hpp>
#include <Utilities/UtilityMethods.hpp>

namespace mnk {

PhysicsSystem::PhysicsSystem(const sf::Vector2f& worldSize) :
    mWorldSize(worldSize) {}

PhysicsSystem::~PhysicsSystem() {}

const sf::Vector2f& PhysicsSystem::getWorldSize() const { return mWorldSize; }
void PhysicsSystem::setWorldSize(const sf::Vector2f& value) { mWorldSize = value; }

void PhysicsSystem::onAddObject(PCKinematicBody& object) {
    // Check that the object does not collide with anything, and move it in such case.
//    for(auto it = getObjectsList().begin(); (*it).get() != &object; ++it) {
//        ContactInformation contact = checkContact(object, **it);
//        if(contact.contactHappened()) {
//            object.sendMessageToEntity(MsgPoseDisplacement(-contact.getContactNormal() * contact.getPenetration(), 0.0f));
//        }
//    }
}

void PhysicsSystem::onUpdateObject(sf::Time dt, PCKinematicBody& object) {
    object.update(dt);
}

void PhysicsSystem::onUpdateEnd(sf::Time dt) {
    for(auto it1 = getObjectsList().begin(); it1 != getObjectsList().end(); ++it1) {
        if((*it1)->isActive()) {
            auto it2 = it1;
            ++it2;
            for(; it2 != getObjectsList().end(); ++it2) {
                if((*it2)->isActive()) {
                    ContactInformation contact = checkContact(**it1, **it2);
                    if(contact.contactHappened()) {
                        (*it1)->sendMessageToEntity(MsgContact(*((*it2)->getpEntity()), contact));
                        (*it2)->sendMessageToEntity(MsgContact(*((*it1)->getpEntity()), contact));
                        resolveCollision(contact.getContactNormal(), contact.getPenetration(), **it1, **it2);
                    }
                }
                if(!(*it1)->isActive()) {
                    break;
                    // This check is done in case it1 gets deactivated as a result of a collision. Do not check anymore collisions in that case.
                }
            }
            checkWorldContact(**it1);
        }
    }
}

void PhysicsSystem::checkWorldContact(PCKinematicBody& component) {
    float left = component.getpContactShape()->getLeft();
    float right = component.getpContactShape()->getRight();
    float width = right - left;
    float up = component.getpContactShape()->getUp();
    float down = component.getpContactShape()->getDown();
    float height = down - up;
    if(right < 0) {
        component.sendMessageToEntity(MsgPoseDisplacement(sf::Vector2f(mWorldSize.x + width, 0), 0));
    } else if(left > mWorldSize.x) {
        component.sendMessageToEntity(MsgPoseDisplacement(sf::Vector2f(-mWorldSize.x - width, 0), 0));
    }
    if(down < 0) {
        component.sendMessageToEntity(MsgPoseDisplacement(sf::Vector2f(0, mWorldSize.y + height), 0));
    } else if(up > mWorldSize.y) {
        component.sendMessageToEntity(MsgPoseDisplacement(sf::Vector2f(0, -mWorldSize.y - height), 0));
    }
}

void PhysicsSystem::resolveCollision(const sf::Vector2f& normal, float penetration, PCKinematicBody& c1, PCKinematicBody& c2) {
    if(c1.isSolid() && c2.isSolid()) {
        // Move bodies so that they are not in contact.
        c1.sendMessageToEntity(MsgPoseDisplacement(-normal * penetration * 0.5f, 0.0f));
        c2.sendMessageToEntity(MsgPoseDisplacement(normal * penetration * 0.5f, 0.0f));

        float m1_plus_m2 = c1.getMass() + c2.getMass();
        float m1_minus_m2 = c1.getMass() - c2.getMass();
        sf::Vector2f vel1 = c1.getLinearVelocity();
        sf::Vector2f vel2 = c2.getLinearVelocity();
        c1.setLinearVelocity((vel1 * m1_minus_m2 + 2.0f * vel2 * c2.getMass()) / m1_plus_m2);
        c2.setLinearVelocity((- vel2 * m1_minus_m2 + 2.0f * vel1 * c1.getMass()) / m1_plus_m2);
    }

}

}
