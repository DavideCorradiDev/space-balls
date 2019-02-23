#ifndef GCUFO_HPP
#define GCUFO_HPP

#include <GameplaySystem/GameplayComponent.hpp>
#include <EntitySystem/EDUfo.hpp>

namespace mnk {

class EntityFactory;

class GCUfo : public GameplayComponent {
public:
    GCUfo(EntityFactory& entityFactory, float speed, float reloadTime, float bulletSpeed, EDUfo::Type type);
    virtual ~GCUfo() = 0;

    virtual void update(sf::Time dt);

protected:
    void destroy();
    virtual void performMovement(sf::Time dt) = 0;
    virtual void attack() = 0;

protected:
    EntityFactory& mEntityFactory;
    float mSpeed;
    float mReloadTime;
    float mTimeSinceLastAttack;
    float mBulletSpeed;
    sf::Vector2f mShipPosition;
    EDUfo::Type mType;
};

}

#endif // GCUFO_HPP
