#ifndef PHYSICSCOMPONENT_HPP
#define PHYSICSCOMPONENT_HPP

#include <EntitySystem/Component.hpp>
#include <PhysicsSystem/ContactShape.hpp>
#include <memory>

namespace mnk {

class PhysicsComponent : public Component {
public:
    PhysicsComponent();
    PhysicsComponent(std::unique_ptr<ContactShape> pContactShape);
    virtual ~PhysicsComponent() = 0;

    virtual void update(sf::Time dt);

    const ContactShape* getpContactShape() const;
    void setpContactShape(std::unique_ptr<ContactShape> pContactShape);

private:
    void setCallbacks();

private:
    std::unique_ptr<ContactShape> mpContactShape;
};

ContactInformation checkContact(const PhysicsComponent& component1, const PhysicsComponent& component2);

}

#endif // PHYSICSCOMPONENT_HPP
