#include <GameplaySystem/GCSpawner.hpp>
#include <GameplaySystem/GSConstants.hpp>
#include <EntitySystem/EntityFactory.hpp>
#include <EntitySystem/EDShip.hpp>
#include <EntitySystem/EDSpaceBall.hpp>
#include <MessageSystem/MsgShipDestroyed.hpp>
#include <MessageSystem/MsgSpaceBallDestroyed.hpp>
#include <MessageSystem/MsgUfoDestroyed.hpp>
#include <MessageSystem/MsgSpaceBallCreated.hpp>
#include <MessageSystem/MsgGameOver.hpp>
#include <MessageSystem/MsgTimedPause.hpp>
#include <MessageSystem/MsgSetPose.hpp>
#include <MessageSystem/MsgChangeStatus.hpp>
#include <MessageSystem/MsgVarScoreChanged.hpp>
#include <MessageSystem/MsgVarLivesChanged.hpp>
#include <MessageSystem/MsgPlaySound.hpp>
#include <MessageSystem/MsgNewLevel.hpp>
#include <Utilities/UtilityMethods.hpp>
#include <Utilities/Randomizer.hpp>
#include <cassert>

namespace mnk {

GCSpawner::GCSpawner(EntityFactory& factory, const sf::Vector2f& worldSize) :
    mFactory(factory),
    mWorldSize(worldSize),
    mLevels(),
    mSpawnLocations(),
    mSmallUfoSpawnLocations(),
    mLargeUfoSpawnLocations(),
    mCurrentLevel(GSConstants::STARTING_LEVEL),
    mNumShips(0),
    mNumBalls(0),
    mNumLives(GSConstants::STARTING_LIVES),
    mScore(0),
    mScoreToNewLife(0),
    pShip(nullptr),
    mUfoTimer(),
    mTimeToUfo(),
    mDumbUfos(0),
    mSmartUfos(0) {

    initializeLevels();
    initializeSpawnLocations(worldSize.x / GSConstants::SPAWN_CELL_SIZE, worldSize.y / GSConstants::SPAWN_CELL_SIZE, static_cast<float>(GSConstants::SPAWN_CELL_SIZE));

    addCallback<MsgShipDestroyed>([this](const MsgShipDestroyed& message) {
        mNumShips--;
        mNumLives--;
    });
    addCallback<MsgSpaceBallDestroyed>([this](const MsgSpaceBallDestroyed& message) {
        mNumBalls--;
        switch(message.size) {
        case EDSpaceBall::Size::Big:
            mScore += GSConstants::SCORE_BIG_BALL;
            mScoreToNewLife += GSConstants::SCORE_BIG_BALL;
            break;
        case EDSpaceBall::Size::Medium:
            mScore += GSConstants::SCORE_MEDIUM_BALL;
            mScoreToNewLife += GSConstants::SCORE_MEDIUM_BALL;
            break;
        case EDSpaceBall::Size::Small:
            mScore += GSConstants::SCORE_SMALL_BALL;
            mScoreToNewLife += GSConstants::SCORE_SMALL_BALL;
            break;
        }
    });
    addCallback<MsgSpaceBallCreated>([this](const MsgSpaceBallCreated& message) {
        mNumBalls++;
    });
    addCallback<MsgUfoDestroyed>([this](const MsgUfoDestroyed& message) {
        mNumBalls--;
        switch(message.type) {
        case EDUfo::Type::Smart:
            mScore += GSConstants::SCORE_SMART_UFO;
            mScoreToNewLife += GSConstants::SCORE_SMART_UFO;
            break;
        case EDUfo::Type::Dumb:
            mScore += GSConstants::SCORE_DUMB_UFO;
            mScoreToNewLife += GSConstants::SCORE_DUMB_UFO;
            break;
        }
    });
}

GCSpawner::~GCSpawner() {}

void GCSpawner::update(sf::Time dt) {
    if(mNumBalls == 0) {
        setupLevel();
    }

    if(mNumShips == 0) {
        if(mNumLives > 0) respawnShip();
        else sendMessageToSystem(MsgGameOver());
    }

    mUfoTimer += dt;
    if(mUfoTimer >= mTimeToUfo) {
        mUfoTimer -=  mTimeToUfo;
        if(mSmartUfos> 0) {
            createUfo(EDUfo::Type::Smart);
            mSmartUfos--;
        } else if(mDumbUfos > 0) {
            createUfo(EDUfo::Type::Dumb);
            mDumbUfos--;
        }
    }

    if(mScoreToNewLife >= GSConstants::SCORE_TO_NEW_LIFE) {
        mScoreToNewLife -= GSConstants::SCORE_TO_NEW_LIFE;
        if(mNumLives < GSConstants::MAX_LIVES) {
            mNumLives++;
            sendMessageToEntity(MsgPlaySound(SoundBufferId::NewLife));
        }
    }
    sendMessageToSystem(MsgVarScoreChanged(mScore));
    sendMessageToSystem(MsgVarLivesChanged(mNumLives));
}

unsigned int GCSpawner::getCurrentLevel() const { return mCurrentLevel + 1; }
unsigned int GCSpawner::getNumLives() const { return mNumLives; }
unsigned int GCSpawner::getScore() const { return mScore; }

void GCSpawner::initializeLevels() {
    for(std::size_t i = 0; i < GSConstants::NUM_OF_LEVELS; ++i) {
        unsigned int nDumbUfos = static_cast<unsigned int>(i/2);
        unsigned int nSmartUfos = nDumbUfos / 2;
        mLevels.push_back(Level(i+1, sf::seconds(40.f - 2*static_cast<float>(i)), nDumbUfos, nSmartUfos));
//        mLevels.push_back(Level(i+1, sf::seconds(5.f), 2, 2));
    }
}

void GCSpawner::initializeSpawnLocations(unsigned int rows, unsigned int cols, float cellSize) {
    for(unsigned int irow = 0; irow < rows; ++irow) {
        for(unsigned int icol = 0; icol < cols; ++icol) {
            // The four central cells are no valid spawn locations, to allow the ship to be put in there.
            if(irow != rows / 2 && irow != rows / 2 - 1 &&
            icol != cols / 2 && icol != cols / 2 - 1) {
                mSpawnLocations.push_back(sf::Vector2f((static_cast<float>(irow) * cellSize + cellSize / 2), (static_cast<float>(icol) * cellSize + cellSize / 2)));
            }
        }
    }
    for(unsigned int irow = 0; irow < rows; ++irow) {
        mSmallUfoSpawnLocations.push_back(sf::Vector2f((static_cast<float>(irow) * cellSize + cellSize / 2), -8.f));
        mSmallUfoSpawnLocations.push_back(sf::Vector2f((static_cast<float>(irow) * cellSize + cellSize / 2), (mWorldSize.y + 8.f)));
        mLargeUfoSpawnLocations.push_back(sf::Vector2f((static_cast<float>(irow) * cellSize + cellSize / 2), -16.f));
        mLargeUfoSpawnLocations.push_back(sf::Vector2f((static_cast<float>(irow) * cellSize + cellSize / 2), (mWorldSize.y + 16.f)));
    }
    for(unsigned int icol = 0; icol < cols; ++icol) {
        mSmallUfoSpawnLocations.push_back(sf::Vector2f(-8.f, (static_cast<float>(icol) * cellSize + cellSize / 2)));
        mSmallUfoSpawnLocations.push_back(sf::Vector2f((mWorldSize.x + 8.f), (static_cast<float>(icol) * cellSize + cellSize / 2)));
        mLargeUfoSpawnLocations.push_back(sf::Vector2f(-16.f, (static_cast<float>(icol) * cellSize + cellSize / 2)));
        mLargeUfoSpawnLocations.push_back(sf::Vector2f((mWorldSize.x + 16.f), (static_cast<float>(icol) * cellSize + cellSize / 2)));
    }

}

void GCSpawner::createShip() {
    pShip = mFactory.createEntity(
        EDShip(GSConstants::SHIP_TURN_SPEED,
            GSConstants::SHIP_ACCELERATION,
            GSConstants::SHIP_RELOAD_TIME,
            GSConstants::SHIP_BULLET_SPEED,
            GSConstants::SHIP_CONTACT_RADIUS,
            GSConstants::SHIP_INVULNERABILITY_TIME_SEC),
        0.5f * mWorldSize, -90.0f);
    mNumShips++;
}
void GCSpawner::createBall() {
    std::size_t positionIndex = 0;
    do {
        positionIndex = static_cast<std::size_t>(Randomizer::random(0, mSpawnLocations.size()-1));
    } while(!mSpawnLocations[positionIndex].free);
    mSpawnLocations[positionIndex].free = false;
    mFactory.createEntity(EDSpaceBall(EDSpaceBall::Size::Big, getOrientationVector(Randomizer::random(0.0f,360.0f))), mSpawnLocations[positionIndex].position);
    mNumBalls++;
}

void GCSpawner::createUfo(EDUfo::Type type) {
    if(type == EDUfo::Type::Smart) {
        std::size_t positionIndex = static_cast<std::size_t>(Randomizer::random(0, mSmallUfoSpawnLocations.size()-1));
        mFactory.createEntity(EDUfo(type), mSmallUfoSpawnLocations[positionIndex]);
    } else {
        std::size_t positionIndex = static_cast<std::size_t>(Randomizer::random(0, mLargeUfoSpawnLocations.size()-1));
        mFactory.createEntity(EDUfo(type), mLargeUfoSpawnLocations[positionIndex]);
    }
    mNumBalls++;
}

void GCSpawner::respawnShip() {
    createShip();
    sendMessageToSystem(MsgTimedPause(sf::seconds(GSConstants::STARTING_PAUSE_DURATION_SEC)));
}

void GCSpawner::setupLevel() {
    // Move ship to middle of the screen.
    if(pShip) {
        pShip->handleMessage(MsgChangeStatus(Status::Deleted));
        mNumShips--;
    }
    createShip();

    // Notify the start of a new level.
    sendMessageToSystem(MsgNewLevel());

    // Reinitialize cells as free.
    for(std::size_t i = 0; i < mSpawnLocations.size(); ++i) {
        mSpawnLocations[i].free = true;
    }

    // Create balls at random locations.
    for(std::size_t i = 0; i < mLevels[mCurrentLevel].numOfBalls; ++i) {
        createBall();
    }

    // Setup number of UFOS.
    mTimeToUfo = mLevels[mCurrentLevel].timeToUfo;
    mDumbUfos = mLevels[mCurrentLevel].dumbUfos;
    mSmartUfos = mLevels[mCurrentLevel].smartUfos;

    // Increase current level.
    if(mCurrentLevel < mLevels.size()-1) mCurrentLevel++;

    // Reset UFO spawn timer.
    mUfoTimer = sf::seconds(0.f);

    // Pause the game for a brief period.
    sendMessageToSystem(MsgTimedPause(sf::seconds(GSConstants::STARTING_PAUSE_DURATION_SEC)));
}

GCSpawner::Level::Level(unsigned int numOfBalls, sf::Time timeToUfo, unsigned int dumbUfos, unsigned int smartUfos) :
    numOfBalls(numOfBalls),
    timeToUfo(timeToUfo),
    dumbUfos(dumbUfos),
    smartUfos(smartUfos) {}

GCSpawner::SpawnLocation::SpawnLocation(const sf::Vector2f& position) :
    position(position),
    free(true) {}

}
