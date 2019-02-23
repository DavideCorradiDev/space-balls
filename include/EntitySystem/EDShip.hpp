#ifndef EDSHIP_HPP
#define EDSHIP_HPP

#include <EntitySystem/EntityData.hpp>
#include <ResourceSystem/TextureHolder.hpp>

namespace mnk {

class EDShip : public EntityData {
public:
    EDShip(float turnSpeed, float acceleration, float reloadTime, float bulletSpeed, float contactRadius, float invulnerabilityTime) :
        turnSpeed(turnSpeed),
        acceleration(acceleration),
        reloadTime(reloadTime),
        bulletSpeed(bulletSpeed),
        contactRadius(contactRadius),
        invulnerabilityTime(invulnerabilityTime) {}
    virtual ~EDShip() {}

public:
    float turnSpeed;
    float acceleration;
    float reloadTime;
    float bulletSpeed;
    float contactRadius;
    float invulnerabilityTime;
};

}

#endif // EDSHIP_HPP
