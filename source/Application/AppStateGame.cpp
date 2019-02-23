#include <Application/AppStateGame.hpp>
#include <Application/AppStateStack.hpp>
#include <Application/AppStatePaused.hpp>
#include <Application/AppStateGameOver.hpp>
#include <Application/AppStateTimedPause.hpp>

#include <EntitySystem/EDSpawner.hpp>
#include <EntitySystem/EDStaticPicture.hpp>

#include <Utilities/UtilityMethods.hpp>
#include <Utilities/Randomizer.hpp>

namespace mnk {

AppStateGame::AppStateGame(AppStateStack& stateStack, Resources& resources) :
    AppState(stateStack, resources),
    mWorld(resources),
    mGuiContainer(),
    mpScoreLabel(nullptr),
    mpLivesTrack(nullptr) {

    initGui();
    mWorld.initGame();
    mResources.musicPlayer.play(MusicId::Game);
}

AppStateGame::~AppStateGame() {}

void AppStateGame::handleInputEvent(const sf::Event& event) {
    switch(event.type) {
    case(sf::Event::EventType::KeyReleased):
        switch(event.key.code) {
        case sf::Keyboard::Key::Escape:
            mStateStack.push(AppState::Ptr(new AppStatePaused(mStateStack, mResources)));
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
    mWorld.handleInputEvent(event);
}

void AppStateGame::handleRealTimeInput() {
    mWorld.handleRealTimeInput();
}

void AppStateGame::update(sf::Time dt) {
    mWorld.update(dt);
    updateGui(dt);
    updateState(dt);
}

void AppStateGame::render() {
    mWorld.render();
    mResources.renderTarget.draw(mGuiContainer);
}

void AppStateGame::initGui() {
    mpScoreLabel = std::make_shared<GuiLabel>("", mResources.fontHolder.get(FontId::MonospaceFont), 32);
    mGuiContainer.addComponent(mpScoreLabel);

    mpLivesTrack = std::make_shared<GuiLivesTrack>(0, mResources.textureHolder.get(TextureId::Ship), sf::IntRect(0,0, 48, 48));
    mpLivesTrack->setScale(0.75f, 0.75f);
    mpLivesTrack->setIconRotation(-90.0f);
    mpLivesTrack->setPosition(0.0f, 0.75f * 48.0f);
    mGuiContainer.addComponent(mpLivesTrack);

    updateGui(sf::Time::Zero);
}

void AppStateGame::updateState(sf::Time dt) {
    if(mWorld.isGameOver()) {
        mStateStack.push(AppState::Ptr(new AppStateGameOver(mStateStack, mResources, mWorld.getGameplaySystem().getScore())));
    } else if(mWorld.isPauseRequest()) {
        mStateStack.push(AppState::Ptr(new AppStateTimedPause(mStateStack, mResources, mWorld.getGameplaySystem().getPauseTime())));
        mWorld.resetPauseRequest();
    }
}

void AppStateGame::updateGui(sf::Time dt) {
    mpScoreLabel->setText(to_string(mWorld.getGameplaySystem().getScore()));
    mpScoreLabel->setPosition(mResources.renderTarget.getSize().x - 0.5f * mpScoreLabel->getLocalBounds().width, 0.5f * mpScoreLabel->getLocalBounds().height);

    mpLivesTrack->setLives(mWorld.getGameplaySystem().getLives());
}

}
