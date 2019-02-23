#include <EntitySystem/Entity.hpp>
#include <EntitySystem/Component.hpp>
#include <cassert>

namespace mnk {

Entity::~Entity() {
    while(mpComponents.begin() != mpComponents.end()) {
        removeComponentFromEntity(**mpComponents.begin(), *this);
    }
}

void Entity::handleMessage(const Message& message) {
    MessageHandler::handleMessage(message);
    sendMessageToComponents(message);
}

void Entity::addComponent(Component& component) {
    mpComponents.push_back(&component);
}

void Entity::removeComponent(Component& component) {
    mpComponents.remove(&component);
}

void Entity::sendMessageToComponents(const Message& message) const {
    for(auto pComponent : mpComponents) {
        pComponent->handleMessage(message);
    }
}

void addComponentToEntity(Component& component, Entity& entity) {
    assert(!component.getpEntity() && "addComponentToEntity - The Component is already member of an entity.");
    component.setpEntity(&entity);
    entity.addComponent(component);
}

void removeComponentFromEntity(Component& component, Entity& entity) {
    assert(component.getpEntity() == &entity && "removeComponentFromEntity - The Component is not member of the Entity.");
    component.setpEntity(nullptr);
    entity.removeComponent(component);
}

}
