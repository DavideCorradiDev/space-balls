#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <EntitySystem/GameObject.hpp>
#include <SFML/Graphics/Transformable.hpp>

namespace mnk {

class Entity;

class Component : public GameObject, public sf::Transformable {
public:
    Component();
    virtual ~Component() = 0;

    Entity* getpEntity() const;
    void setpEntity(Entity* pEntity);
    void sendMessageToEntity(const Message& message) const;

private:
    Entity* mpEntity;
};

}

#endif // COMPONENT_HPP
