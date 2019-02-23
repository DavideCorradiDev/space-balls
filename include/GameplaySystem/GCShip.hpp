#ifndef GCSHIP_HPP
#define GCSHIP_HPP

#include <GameplaySystem/GameplayComponent.hpp>

namespace mnk {

class EntityFactory;

class GCShip : public GameplayComponent {
public:
    GCShip(EntityFactory& entityFactory, float turnSpeed, float acceleration, float reloadTime, float bulletSpeed, float gunPosition, float invulnerabilityTime);
    virtual ~GCShip();

    virtual void update(sf::Time dt);

    float getTurnSpeed() const;
    void setTurnSpeed(float value);
    float getAcceleration() const;
    void setAcceleration(float value);
    float getReloadTime() const;
    void setReloadTime(float value);
    float getBulletSpeed() const;
    void setBulletSpeed(float value);
    float getGunPosition() const;
    void setGunPosition(float value);

    void setInvulnerable();

private:
    void destroy();

private:
    EntityFactory& mEntityFactory;
    float mTurnSpeed;
    float mAcceleration;
    float mReloadTime;
    float mTimeSinceLastAttack;
    float mBulletSpeed;
    float mGunPosition;
    bool mAccelerating;
    float mInvulnerabilityTime;
    float mCurrentInvulnerabilityTime;
    bool mInvulnerable;
    float mBlinkTime;
    float mCurrentBlinkTime;
    bool mVisible;
};

}

#endif // GCSHIP_HPP
