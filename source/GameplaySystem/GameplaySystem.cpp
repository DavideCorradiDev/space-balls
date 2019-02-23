#include <GameplaySystem/GameplaySystem.hpp>
#include <GameplaySystem/GSConstants.hpp>
#include <MessageSystem/MsgGameOver.hpp>
#include <MessageSystem/MsgTimedPause.hpp>
#include <MessageSystem/MsgShipDestroyed.hpp>
#include <MessageSystem/MsgSpaceBallDestroyed.hpp>
#include <MessageSystem/MsgVarScoreChanged.hpp>
#include <MessageSystem/MsgVarLivesChanged.hpp>

namespace mnk {

GameplaySystem::GameplaySystem() :
    mGameOver(false),
    mPauseRequest(false),
    mPauseTime(sf::seconds(0.0f)),
    mScore(0),
    mLives(0) {
    addCallback<MsgGameOver>([this](const MsgGameOver& message) {
        mGameOver = true;
    });
    addCallback<MsgTimedPause>([this](const MsgTimedPause& message) {
        mPauseRequest = true;
        mPauseTime = message.pauseTime;
    });
    addCallback<MsgShipDestroyed>([this](const MsgShipDestroyed& message) {
        mLives--;
    });
    addCallback<MsgSpaceBallDestroyed>([this](const MsgSpaceBallDestroyed& message) {
        switch(message.size) {
        case EDSpaceBall::Size::Big:
            mScore += GSConstants::SCORE_BIG_BALL;
            break;
        case EDSpaceBall::Size::Medium:
            mScore += GSConstants::SCORE_MEDIUM_BALL;
            break;
        case EDSpaceBall::Size::Small:
            mScore += GSConstants::SCORE_SMALL_BALL;
            break;
        }
    });
    addCallback<MsgVarScoreChanged>([this](const MsgVarScoreChanged& message) {
        mScore = message.score;
    });
    addCallback<MsgVarLivesChanged>([this](const MsgVarLivesChanged& message) {
        mLives = message.lives;
    });
}

GameplaySystem::~GameplaySystem() {}

bool GameplaySystem::isGameOver() const { return mGameOver; }
bool GameplaySystem::isPauseRequest() const { return mPauseRequest; }
sf::Time GameplaySystem::getPauseTime() const { return mPauseTime; }

void GameplaySystem::resetPauseRequest() {
    mPauseRequest = false;
    mPauseTime = sf::seconds(0.0f);
}

unsigned int GameplaySystem::getScore() const { return mScore; }
unsigned int GameplaySystem::getLives() const { return mLives; }

void GameplaySystem::onUpdateObject(sf::Time dt, GameplayComponent& object) {
    object.update(dt);
}

}
