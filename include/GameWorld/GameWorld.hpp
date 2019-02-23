#ifndef GAMEWORLD_HPP
#define GAMEWORLD_HPP

#include <ResourceSystem/Resources.hpp>
#include <EntitySystem/EntitySystem.hpp>
#include <InputSystem/InputSystem.hpp>
#include <GameplaySystem/GameplaySystem.hpp>
#include <PhysicsSystem/PhysicsSystem.hpp>
#include <AudioSystem/AudioSystem.hpp>
#include <RenderSystem/RenderSystem.hpp>
#include <EntitySystem/EntityFactory.hpp>

namespace mnk {

class GameWorld {
public:
    GameWorld(Resources& resources);

    void handleInputEvent(const sf::Event& event);
    void handleRealTimeInput();
    void update(sf::Time dt);
    void render();

    void initGame();
    void initMenu();

    const EntitySystem& getEntitySystem() const;
    const InputSystem& getInputSystem() const;
    const GameplaySystem& getGameplaySystem() const;
    const PhysicsSystem& getPhysicsSystem() const;
    const AudioSystem& getAudioSystem() const;
    const RenderSystem& getRenderSystem() const;

    bool isGameOver() const;
    bool isPauseRequest() const;
    void resetPauseRequest();

private:
    Resources& mResources;
    EntitySystem mEntitySystem;
    InputSystem mInputSystem;
    GameplaySystem mGameplaySystem;
    PhysicsSystem mPhysicsSystem;
    AudioSystem mAudioSystem;
    RenderSystem mRenderSystem;
    EntityFactory mEntityFactory;
};

}

#endif // GAMEWORLD_HPP
