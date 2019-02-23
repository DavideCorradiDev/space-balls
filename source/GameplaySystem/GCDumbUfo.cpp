#include <GameplaySystem/GCDumbUfo.hpp>
#include <EntitySystem/EntityFactory.hpp>
#include <Utilities/Randomizer.hpp>
#include <Utilities/UtilityMethods.hpp>
#include <MessageSystem/MsgPoseDisplacement.hpp>
#include <MessageSystem/MsgPlaySound.hpp>
#include <EntitySystem/EDBullet.hpp>

namespace mnk {

GCDumbUfo::GCDumbUfo(EntityFactory& entityFactory, float speed, float reloadTime, float bulletSpeed, EDUfo::Type type) :
    GCUfo(entityFactory, speed, reloadTime, bulletSpeed, type),
    mMovementDirection(getOrientationVector(Randomizer::random(0.f, 360.f))) {}

GCDumbUfo::~GCDumbUfo() {}

void GCDumbUfo::performMovement(sf::Time dt) {
    sendMessageToEntity(MsgPoseDisplacement(mMovementDirection * mSpeed * dt.asSeconds(), 0.f));
}

void GCDumbUfo::attack() {
    sf::Vector2f shootingDirection = getOrientationVector(Randomizer::random(0.f, 360.f));
    mEntityFactory.createEntity(EDBullet(shootingDirection * mBulletSpeed, false), getPosition());
    sendMessageToEntity(MsgPlaySound(SoundBufferId::Shoot));
}

}
