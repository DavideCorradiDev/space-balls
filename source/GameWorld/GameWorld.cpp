#include <GameWorld/GameWorld.hpp>
#include <EntitySystem/EDSpawner.hpp>
#include <EntitySystem/EDStaticPicture.hpp>
#include <EntitySystem/EDSpaceBall.hpp>
#include <GameplaySystem/GSConstants.hpp>
#include <Utilities/UtilityMethods.hpp>
#include <Utilities/Randomizer.hpp>
#include <vector>

namespace mnk {

struct SpawnLocation {
    SpawnLocation(const sf::Vector2f& position);
    sf::Vector2f position;
    bool free;
};

SpawnLocation::SpawnLocation(const sf::Vector2f& position) :
    position(position),
    free(true) {}

GameWorld::GameWorld(Resources& resources) :
    mResources(resources),
    mEntitySystem(),
    mInputSystem(),
    mGameplaySystem(),
    mPhysicsSystem(sf::Vector2f(resources.renderTarget.getSize())),
    mAudioSystem(),
    mRenderSystem(resources.renderTarget),
    mEntityFactory(resources, mEntitySystem, mGameplaySystem, mInputSystem, mPhysicsSystem, mAudioSystem, mRenderSystem) {}

void GameWorld::handleInputEvent(const sf::Event& event) {
    mInputSystem.handleInputEvent(event);
}

void GameWorld::handleRealTimeInput() {
    mInputSystem.handleRealTimeInput();
}

void GameWorld::update(sf::Time dt) {
    mEntitySystem.update(dt);
    mInputSystem.update(dt);
    mGameplaySystem.update(dt);
    mPhysicsSystem.update(dt);
    mAudioSystem.update(dt);
    mRenderSystem.update(dt);
}

void GameWorld::render() {
    mRenderSystem.render();
}

void GameWorld::initGame() {
    mEntityFactory.createEntity(EDStaticPicture(TextureId::SpaceBackground), 0.5f * sf::Vector2f(mResources.renderTarget.getSize()));
    mEntityFactory.createEntity(EDSpawner(sf::Vector2f(mResources.renderTarget.getSize())));
}

void GameWorld::initMenu() {
    std::vector<SpawnLocation> mSpawnLocations;
    for(unsigned int irow = 0; irow < mResources.renderTarget.getSize().x / GSConstants::SPAWN_CELL_SIZE; ++irow) {
        for(unsigned int icol = 0; icol < mResources.renderTarget.getSize().y / GSConstants::SPAWN_CELL_SIZE; ++icol) {
            mSpawnLocations.push_back(sf::Vector2f(static_cast<float>(irow * GSConstants::SPAWN_CELL_SIZE + GSConstants::SPAWN_CELL_SIZE / 2), static_cast<float>(icol * GSConstants::SPAWN_CELL_SIZE + GSConstants::SPAWN_CELL_SIZE / 2)));
        }
    }

    mEntityFactory.createEntity(EDStaticPicture(TextureId::SpaceBackground), 0.5f * sf::Vector2f(mResources.renderTarget.getSize()));

    for(unsigned int i = 0; i < GSConstants::MENU_BALLS_BIG; ++i) {
        std::size_t positionIndex = static_cast<std::size_t>(Randomizer::random(0, mSpawnLocations.size()-1));
        mSpawnLocations[positionIndex].free = false;
        mEntityFactory.createEntity(EDSpaceBall(EDSpaceBall::Size::Big, getOrientationVector(Randomizer::random(0.0f,360.0f))), mSpawnLocations[positionIndex].position);
    }
    for(unsigned int i = 0; i < GSConstants::MENU_BALLS_MEDIUM; ++i) {
        std::size_t positionIndex = static_cast<std::size_t>(Randomizer::random(0, mSpawnLocations.size()-1));
        mSpawnLocations[positionIndex].free = false;
        mEntityFactory.createEntity(EDSpaceBall(EDSpaceBall::Size::Medium, getOrientationVector(Randomizer::random(0.0f,360.0f))), mSpawnLocations[positionIndex].position);
    }
    for(unsigned int i = 0; i < GSConstants::MENU_BALLS_SMALL; ++i) {
        std::size_t positionIndex = static_cast<std::size_t>(Randomizer::random(0, mSpawnLocations.size()-1));
        mSpawnLocations[positionIndex].free = false;
        mEntityFactory.createEntity(EDSpaceBall(EDSpaceBall::Size::Small, getOrientationVector(Randomizer::random(0.0f,360.0f))), mSpawnLocations[positionIndex].position);
    }
}

const EntitySystem& GameWorld::getEntitySystem() const { return mEntitySystem; }
const InputSystem& GameWorld::getInputSystem() const { return mInputSystem; }
const GameplaySystem& GameWorld::getGameplaySystem() const { return mGameplaySystem; }
const PhysicsSystem& GameWorld::getPhysicsSystem() const { return mPhysicsSystem; }
const AudioSystem& GameWorld::getAudioSystem() const { return mAudioSystem; }
const RenderSystem& GameWorld::getRenderSystem() const { return mRenderSystem; }

bool GameWorld::isGameOver() const { return mGameplaySystem.isGameOver(); }
bool GameWorld::isPauseRequest() const { return mGameplaySystem.isPauseRequest(); }
void GameWorld::resetPauseRequest() { mGameplaySystem.resetPauseRequest(); }

}
