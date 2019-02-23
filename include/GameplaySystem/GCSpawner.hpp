#ifndef GCSPAWNER_HPP
#define GCSPAWNER_HPP

#include <GameplaySystem/GameplayComponent.hpp>
#include <EntitySystem/EDUfo.hpp>
#include <RenderSystem/RCLabel.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>

namespace mnk {

class EntityFactory;

class GCSpawner : public GameplayComponent {
public:
    GCSpawner(EntityFactory& factory, const sf::Vector2f& worldSize);
    virtual ~GCSpawner();

    virtual void update(sf::Time dt);

    unsigned int getCurrentLevel() const;
    unsigned int getNumLives() const;
    unsigned int getScore() const;

private:
    struct Level {
        Level(unsigned int numOfBalls, sf::Time timeToUfo, unsigned int dumbUfos, unsigned int smartUfos);
        unsigned int numOfBalls;
        sf::Time timeToUfo;
        unsigned int dumbUfos;
        unsigned int smartUfos;
    };

    struct SpawnLocation {
        SpawnLocation(const sf::Vector2f& position);
        sf::Vector2f position;
        bool free;
    };

private:
    void initializeLevels();
    void initializeSpawnLocations(unsigned int rows, unsigned int cols, float cellSize);
    void createShip();
    void createBall();
    void createUfo(EDUfo::Type type);
    void respawnShip();
    void setupLevel();

private:
    EntityFactory& mFactory;
    sf::Vector2f mWorldSize;
    std::vector<Level> mLevels;
    std::vector<SpawnLocation> mSpawnLocations;
    std::vector<sf::Vector2f> mSmallUfoSpawnLocations;
    std::vector<sf::Vector2f> mLargeUfoSpawnLocations;
    unsigned int mCurrentLevel;
    unsigned int mNumShips;
    unsigned int mNumBalls;
    unsigned int mNumLives;
    unsigned int mScore;
    unsigned int mScoreToNewLife;
    Entity* pShip;
    sf::Time mUfoTimer;
    sf::Time mTimeToUfo;
    unsigned int mDumbUfos;
    unsigned int mSmartUfos;
};

}

#endif // GCSPAWNER_HPP
