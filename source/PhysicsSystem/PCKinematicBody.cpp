#include <PhysicsSystem/PCKinematicBody.hpp>
#include <PhysicsSystem/PSConstants.hpp>
#include <MessageSystem/MsgPoseDisplacement.hpp>
#include <MessageSystem/MsgVelocityVariation.hpp>
#include <MessageSystem/MsgAccelerationVariation.hpp>
#include <algorithm>
#include <cassert>

namespace mnk {



PCKinematicBody::PCKinematicBody() :
    PhysicsComponent(),
    mLinearVelocity(0.0, 0.0),
    mAngularVelocity(0.0),
    mLinearAcceleration(0.0, 0.0),
    mAngularAcceleration(0.0),
    mLinearVelocityLimit(PSConstants::LINEAR_VELOCITY_LIMIT),
    mAngularVelocityLimit(PSConstants::ANGULAR_VELOCITY_LIMIT),
    mLinearAccelerationLimit(PSConstants::LINEAR_ACCELERATION_LIMIT),
    mAngularAccelerationLimit(PSConstants::ANGULAR_ACCELERATION_LIMIT),
    mMass(1.0),
    mSolid(true) {
    setCallbacks();
}

PCKinematicBody::PCKinematicBody(std::unique_ptr<ContactShape> pContactShape) :
    PhysicsComponent(std::move(pContactShape)),
    mLinearVelocity(0.0, 0.0),
    mAngularVelocity(0.0),
    mLinearAcceleration(0.0, 0.0),
    mAngularAcceleration(0.0),
    mLinearVelocityLimit(PSConstants::LINEAR_VELOCITY_LIMIT),
    mAngularVelocityLimit(PSConstants::ANGULAR_VELOCITY_LIMIT),
    mLinearAccelerationLimit(PSConstants::LINEAR_ACCELERATION_LIMIT),
    mAngularAccelerationLimit(PSConstants::ANGULAR_ACCELERATION_LIMIT),
    mSolid(true) {
    setCallbacks();
}

PCKinematicBody::~PCKinematicBody() {}

void PCKinematicBody::update(sf::Time dt) {
    setLinearVelocity(mLinearVelocity + mLinearAcceleration * dt.asSeconds());
    setAngularVelocity(mAngularVelocity + mAngularAcceleration * dt.asSeconds());
    sendMessageToEntity(MsgPoseDisplacement(mLinearVelocity * dt.asSeconds(), mAngularVelocity * dt.asSeconds()));
}

const sf::Vector2f& PCKinematicBody::getLinearVelocity() const { return mLinearVelocity; }
void PCKinematicBody::setLinearVelocity(sf::Vector2f value) {
    value.x = std::min(std::max(value.x, -mLinearVelocityLimit.x), mLinearVelocityLimit.x);
    value.y = std::min(std::max(value.y, -mLinearVelocityLimit.y), mLinearVelocityLimit.y);
    mLinearVelocity = value;
}
float PCKinematicBody::getAngularVelocity() const { return mAngularVelocity; }
void PCKinematicBody::setAngularVelocity(float value) {
    value = std::min(std::max(value, -mAngularVelocityLimit), mAngularVelocityLimit);
    mAngularVelocity = value;
}
const sf::Vector2f& PCKinematicBody::getLinearAcceleration() const { return mLinearAcceleration; }
void PCKinematicBody::setLinearAcceleration(sf::Vector2f value){
    value.x = std::min(std::max(value.x, -mLinearAccelerationLimit.x), mLinearAccelerationLimit.x);
    value.y = std::min(std::max(value.y, -mLinearAccelerationLimit.y), mLinearAccelerationLimit.y);
    mLinearAcceleration = value;
}
float PCKinematicBody::getAngularAcceleration() const { return mAngularAcceleration; }
void PCKinematicBody::setAngularAcceleration(float value) {
    value = std::min(std::max(value, -mAngularAccelerationLimit), mAngularAccelerationLimit);
    mAngularAcceleration = value;
}

const sf::Vector2f& PCKinematicBody::getLinearVelocityLimit() const { return mLinearVelocityLimit; }
void PCKinematicBody::setLinearVelocityLimit(sf::Vector2f value) {
    value.x = std::min(std::max(value.x, -PSConstants::LINEAR_VELOCITY_LIMIT.x), PSConstants::LINEAR_VELOCITY_LIMIT.x);
    value.y = std::min(std::max(value.y, -PSConstants::LINEAR_VELOCITY_LIMIT.y), PSConstants::LINEAR_VELOCITY_LIMIT.y);
    mLinearVelocityLimit = value;
}
float PCKinematicBody::getAngularVelocityLimit() const { return mAngularVelocityLimit; }
void PCKinematicBody::setAngularVelocityLimit(float value) {
    value = std::min(std::max(value, -PSConstants::ANGULAR_VELOCITY_LIMIT), PSConstants::ANGULAR_VELOCITY_LIMIT);
    mAngularVelocityLimit = value;
}
const sf::Vector2f& PCKinematicBody::getLinearAccelerationLimit() const { return mLinearAccelerationLimit; }
void PCKinematicBody::setLinearAccelerationLimit(sf::Vector2f value){
    value.x = std::min(std::max(value.x, -PSConstants::LINEAR_ACCELERATION_LIMIT.x), PSConstants::LINEAR_ACCELERATION_LIMIT.x);
    value.y = std::min(std::max(value.y, -PSConstants::LINEAR_ACCELERATION_LIMIT.y), PSConstants::LINEAR_ACCELERATION_LIMIT.y);
    mLinearAccelerationLimit = value;
}
float PCKinematicBody::getAngularAccelerationLimit() const { return mAngularAccelerationLimit; }
void PCKinematicBody::setAngularAccelerationLimit(float value) {
    value = std::min(std::max(value, -PSConstants::ANGULAR_ACCELERATION_LIMIT), PSConstants::ANGULAR_ACCELERATION_LIMIT);
    mAngularAccelerationLimit = value;
}

float PCKinematicBody::getMass() const { return mMass; }
void PCKinematicBody::setMass(float value) {
    assert(value > 0);
    mMass = value;
}

bool PCKinematicBody::isSolid() const { return mSolid; }
void PCKinematicBody::setSolid(bool value) { mSolid = value; }

void PCKinematicBody::setCallbacks() {
    addCallback<MsgVelocityVariation>([this](const MsgVelocityVariation& message) {
        setLinearVelocity(mLinearVelocity + message.linear);
        setAngularVelocity(mAngularVelocity + message.angularDeg);
    });
    addCallback<MsgAccelerationVariation>([this](const MsgAccelerationVariation& message) {
        setLinearAcceleration(mLinearAcceleration + message.linear);
        setAngularAcceleration(mAngularAcceleration + message.angularDeg);
    });
}

}
