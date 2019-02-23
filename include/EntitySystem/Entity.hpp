#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <EntitySystem/GameObject.hpp>
#include <list>

namespace mnk {

class Component;

class Entity : public GameObject {
public:
    virtual ~Entity();

    virtual void handleMessage(const Message& message);
    void addComponent(Component& component);
    void removeComponent(Component& component);
    void sendMessageToComponents(const Message& message) const;

private:
    std::list<Component*> mpComponents;
};

void addComponentToEntity(Component& component, Entity& entity);
void removeComponentFromEntity(Component& component, Entity& entity);

}

#endif // ENTITY_HPP
