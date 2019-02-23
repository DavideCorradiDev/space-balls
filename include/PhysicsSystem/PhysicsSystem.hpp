#ifndef PHYSICSSYSTEM_HPP
#define PHYSICSSYSTEM_HPP

#include <EntitySystem/GameSystem.hpp>
#include <PhysicsSystem/PCKinematicBody.hpp>

namespace mnk {

class PhysicsSystem : public GameSystem<PCKinematicBody> {
public:
    PhysicsSystem(const sf::Vector2f& worldSize);
    virtual ~PhysicsSystem();

    const sf::Vector2f& getWorldSize() const;
    void setWorldSize(const sf::Vector2f& value);

private:
    virtual void onAddObject(PCKinematicBody& object);
    virtual void onUpdateObject(sf::Time dt, PCKinematicBody& object);
    virtual void onUpdateEnd(sf::Time dt);
    void checkWorldContact(PCKinematicBody& component);
    void resolveCollision(const sf::Vector2f& normal, float penetration, PCKinematicBody& c1, PCKinematicBody& c2);

private:
    sf::Vector2f mWorldSize;
};

}

#endif // PHYSICSSYSTEM_HPP
