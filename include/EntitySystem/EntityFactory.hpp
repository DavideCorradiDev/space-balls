#ifndef ENTITYFACTORY_HPP
#define ENTITYFACTORY_HPP

#include <EntitySystem/Entity.hpp>
#include <EntitySystem/EntityData.hpp>
#include <ResourceSystem/Resources.hpp>
#include <SFML/System/Vector2.hpp>
#include <functional>
#include <map>
#include <typeindex>
#include <memory>

namespace mnk {

class EntitySystem;
class GameplaySystem;
class InputSystem;
class PhysicsSystem;
class AudioSystem;
class RenderSystem;

class EntityFactory {
public:
    EntityFactory(const Resources& resources, EntitySystem& entitySystem, GameplaySystem& gameplaySystem, InputSystem& inputSystem, PhysicsSystem& physicsSystem, AudioSystem& audioSystem, RenderSystem& renderSystem);

    Entity* createEntity(const EntityData& data, const sf::Vector2f& position = sf::Vector2f(0,0), float orientationDeg = 0);

private:
    typedef std::function<Entity*(const EntityData&)> FactoryFunction;
    typedef std::map<std::type_index, FactoryFunction> FactoryFunctionsMap;

private:
    template <typename EntityDataType>
    void addFactoryFunction(std::function<Entity*(const EntityDataType&)> factoryFunction);
    void initializeFactoryFunctionsMap();

private:
    FactoryFunctionsMap mFactoryFunctions;
    Resources mResources;                   // Must have value, not reference. If not, for some not determined reason it seg-faults when accessing resources.
    EntitySystem& mEntitySystem;
    GameplaySystem& mGameplaySystem;
    InputSystem& mInputSystem;
    PhysicsSystem& mPhysicsSystem;
    AudioSystem& mAudioSystem;
    RenderSystem& mRenderSystem;
};

template <typename EntityDataType>
void EntityFactory::addFactoryFunction(std::function<Entity*(const EntityDataType&)> factoryFunction) {
    mFactoryFunctions.insert(std::make_pair(std::type_index(typeid(EntityDataType)), [=](const EntityData& data) {
        return factoryFunction(static_cast<const EntityDataType&>(data));
    }));
}

}

#endif // ENTITYFACTORY_HPP
