#include <GameplaySystem/GCShip.hpp>

#include <MessageSystem/MsgChangeStatus.hpp>
#include <MessageSystem/MsgCmdTurnLeft.hpp>
#include <MessageSystem/MsgCmdTurnRight.hpp>
#include <MessageSystem/MsgCmdAccelerate.hpp>
#include <MessageSystem/MsgCmdStop.hpp>
#include <MessageSystem/MsgCmdAttack.hpp>
#include <MessageSystem/MsgPoseDisplacement.hpp>
#include <MessageSystem/MsgVelocityVariation.hpp>
#include <MessageSystem/MsgContact.hpp>
#include <MessageSystem/MsgContactBullet.hpp>
#include <MessageSystem/MsgContactShip.hpp>
#include <MessageSystem/MsgContactSpaceBall.hpp>
#include <MessageSystem/MsgPlaySound.hpp>
#include <MessageSystem/MsgShipDestroyed.hpp>
#include <MessageSystem/MsgSetVisible.hpp>
#include <MessageSystem/MsgShipPosition.hpp>

#include <EntitySystem/EntityFactory.hpp>
#include <EntitySystem/EDBullet.hpp>
#include <EntitySystem/EDShip.hpp>
#include <EntitySystem/EDExplosion.hpp>

#include <Utilities/UtilityMethods.hpp>

#include <iostream>

namespace mnk {

GCShip::GCShip(EntityFactory& entityFactory, float turnSpeed, float acceleration, float reloadTime, float bulletSpeed, float gunPosition, float invulnerabilityTime) :
    GameplayComponent(),
    mEntityFactory(entityFactory),
    mTurnSpeed(turnSpeed),
    mAcceleration(acceleration),
    mReloadTime(reloadTime),
    mTimeSinceLastAttack(reloadTime),
    mBulletSpeed(bulletSpeed),
    mGunPosition(gunPosition),
    mAccelerating(false),
    mInvulnerabilityTime(invulnerabilityTime),
    mCurrentInvulnerabilityTime(mInvulnerabilityTime),
    mInvulnerable(true),
    mBlinkTime(invulnerabilityTime / 6.0f),
    mCurrentBlinkTime(mBlinkTime),
    mVisible(true) {

    addCallback<MsgCmdTurnLeft>([this](const MsgCmdTurnLeft& message) {
        sendMessageToEntity(MsgPoseDisplacement(sf::Vector2f(0.0, 0.0), - mTurnSpeed * message.dt.asSeconds()));
    });
    addCallback<MsgCmdTurnRight>([this](const MsgCmdTurnRight& message) {
        sendMessageToEntity(MsgPoseDisplacement(sf::Vector2f(0.0, 0.0), mTurnSpeed * message.dt.asSeconds()));
    });
    addCallback<MsgCmdAttack>([this](const MsgCmdAttack& message) {
        if(mTimeSinceLastAttack >= mReloadTime) {
            mEntityFactory.createEntity(EDBullet(getOrientationVector(getRotation()) * mBulletSpeed, true), getPosition() + getOrientationVector(getRotation()) * mGunPosition);
            mTimeSinceLastAttack = 0.0;
            sendMessageToEntity(MsgPlaySound(SoundBufferId::Shoot));
        }
    });
    addCallback<MsgCmdAccelerate>([this](const MsgCmdAccelerate& message) {
        mAccelerating = true;
    });
    addCallback<MsgCmdStop>([this](const MsgCmdStop& message) {
        mAccelerating = false;
    });
    addCallback<MsgContact>([this](const MsgContact& message) {
        if(!mInvulnerable) message.otherEntity.handleMessage(MsgContactShip(true));
    });
    addCallback<MsgContactBullet>([this](const MsgContactBullet& message) {
        if(!mInvulnerable && !message.ofPlayer) destroy();
    });
    addCallback<MsgContactSpaceBall>([this](const MsgContactSpaceBall& message) {
        if(!mInvulnerable) destroy();
    });
    addCallback<MsgContactShip>([this](const MsgContactShip& message) {
        if(!mInvulnerable) destroy();
    });
}

GCShip::~GCShip() {}

void GCShip::update(sf::Time dt) {
    mTimeSinceLastAttack += dt.asSeconds();
    if(mInvulnerable) {
        mCurrentInvulnerabilityTime -= dt.asSeconds();
        mCurrentBlinkTime -= dt.asSeconds();
        if(mCurrentInvulnerabilityTime <= 0.0f) {
            mInvulnerable = false;
            mVisible = true;
        } else if(mCurrentBlinkTime <= 0.0f) {
            mCurrentBlinkTime += mBlinkTime;
            mVisible = !mVisible;
        }
        sendMessageToEntity(MsgSetVisible(mVisible));
    }
    if(mAccelerating) {
        sendMessageToEntity(MsgVelocityVariation(getOrientationVector(getRotation()) * mAcceleration * dt.asSeconds(), 0.0));
    }

    sendMessageToSystem(MsgShipPosition(getPosition()));
}

float GCShip::getTurnSpeed() const { return mTurnSpeed; }
void GCShip::setTurnSpeed(float value) { mTurnSpeed = value; }
float GCShip::getAcceleration() const { return mAcceleration; }
void GCShip::setAcceleration(float value) { mAcceleration = value; }
float GCShip::getReloadTime() const { return mReloadTime; }
void GCShip::setReloadTime(float value) { mReloadTime = value; }
float GCShip::getBulletSpeed() const { return mBulletSpeed; }
void GCShip::setBulletSpeed(float value) { mBulletSpeed = value; }
float GCShip::getGunPosition() const { return mGunPosition; }
void GCShip::setGunPosition(float value) { mGunPosition = value; }

void GCShip::setInvulnerable() {
    mInvulnerable = true;
    mVisible = true;
    mCurrentInvulnerabilityTime = mInvulnerabilityTime;
    mCurrentBlinkTime = mBlinkTime;
}

void GCShip::destroy() {
    sendMessageToEntity(MsgChangeStatus(Status::Deleted));
    sendMessageToEntity(MsgPlaySound(SoundBufferId::Explosion));
    sendMessageToSystem(MsgShipDestroyed());
    mEntityFactory.createEntity(EDExplosion(), getPosition());
}

}
