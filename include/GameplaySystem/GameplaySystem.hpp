#ifndef GAMEPLAYSYSTEM_HPP
#define GAMEPLAYSYSTEM_HPP

#include <EntitySystem/GameSystem.hpp>
#include <GameplaySystem/GameplayComponent.hpp>
#include <SFML/System/Time.hpp>

namespace mnk {

class GameplaySystem : public GameSystem<GameplayComponent> {
public:
    GameplaySystem();
    virtual ~GameplaySystem();

    bool isGameOver() const;
    bool isPauseRequest() const;
    sf::Time getPauseTime() const;
    void resetPauseRequest();
    unsigned int getScore() const;
    unsigned int getLives() const;

private:
    virtual void onUpdateObject(sf::Time dt, GameplayComponent& object);

private:
    bool mGameOver;
    bool mPauseRequest;
    sf::Time mPauseTime;
    unsigned int mScore;
    unsigned int mLives;
};

}

#endif // GAMEPLAYSYSTEM_HPP
