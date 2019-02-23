#ifndef PCKINEMATICBODY_HPP
#define PCKINEMATICBODY_HPP

#include <PhysicsSystem/PhysicsComponent.hpp>

namespace mnk {

class PCKinematicBody : public PhysicsComponent {
public:
    PCKinematicBody();
    PCKinematicBody(std::unique_ptr<ContactShape> pContactShape);
    virtual ~PCKinematicBody();

    virtual void update(sf::Time dt);

    const sf::Vector2f& getLinearVelocity() const;
    void setLinearVelocity(sf::Vector2f value);
    float getAngularVelocity() const;
    void setAngularVelocity(float value);
    const sf::Vector2f& getLinearAcceleration() const;
    void setLinearAcceleration(sf::Vector2f value);
    float getAngularAcceleration() const;
    void setAngularAcceleration(float value);

    const sf::Vector2f& getLinearVelocityLimit() const;
    void setLinearVelocityLimit(sf::Vector2f value);
    float getAngularVelocityLimit() const;
    void setAngularVelocityLimit(float value);
    const sf::Vector2f& getLinearAccelerationLimit() const;
    void setLinearAccelerationLimit(sf::Vector2f value);
    float getAngularAccelerationLimit() const;
    void setAngularAccelerationLimit(float value);

    float getMass() const;
    void setMass(float value);

    bool isSolid() const;
    void setSolid(bool value);

private:
    void setCallbacks();

private:
    sf::Vector2f mLinearVelocity;
    float mAngularVelocity;
    sf::Vector2f mLinearAcceleration;
    float mAngularAcceleration;

    sf::Vector2f mLinearVelocityLimit;
    float mAngularVelocityLimit;
    sf::Vector2f mLinearAccelerationLimit;
    float mAngularAccelerationLimit;

    float mMass;
    bool mSolid;
};

}

#endif // PCKINEMATICBODY_HPP
