#ifndef ENTITYSYSTEM_HPP
#define ENTITYSYSTEM_HPP

#include <EntitySystem/GameSystem.hpp>
#include <EntitySystem/Entity.hpp>

namespace mnk {

class EntitySystem : public GameSystem<Entity> {
public:
    virtual ~EntitySystem();
};

}

#endif // ENTITYSYSTEM_HPP
