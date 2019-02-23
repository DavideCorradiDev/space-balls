#include <GameplaySystem/GCSmartUfo.hpp>
#include <EntitySystem/EntityFactory.hpp>
#include <MessageSystem/MsgPoseDisplacement.hpp>
#include <MessageSystem/MsgPlaySound.hpp>
#include <EntitySystem/EDBullet.hpp>
#include <Utilities/UtilityMethods.hpp>
#include <Utilities/Randomizer.hpp>
#include <cmath>

namespace mnk {

GCSmartUfo::GCSmartUfo(EntityFactory& entityFactory, float speed, float reloadTime, float bulletSpeed, EDUfo::Type type, float shootDeviation) :
    GCUfo(entityFactory, speed, reloadTime, bulletSpeed, type),
    mMovementDirection(),
    mShootDeviation(shootDeviation) {}

GCSmartUfo::~GCSmartUfo() {}

void GCSmartUfo::performMovement(sf::Time dt) {
    mMovementDirection = normalize(mShipPosition - getPosition());
    sendMessageToEntity(MsgPoseDisplacement(mMovementDirection * mSpeed * dt.asSeconds(), 0.f));
}

void GCSmartUfo::attack() {
    sf::Vector2f distanceVector = mShipPosition - getPosition();
    float perfectShootingAngle = 180.f * atan2(distanceVector.y, distanceVector.x) / Constants::PI;
    sf::Vector2f shootingDirection = getOrientationVector(perfectShootingAngle + Randomizer::random(-mShootDeviation, mShootDeviation));
    mEntityFactory.createEntity(EDBullet(shootingDirection * mBulletSpeed, false), getPosition());
    sendMessageToEntity(MsgPlaySound(SoundBufferId::Shoot));
}

}
