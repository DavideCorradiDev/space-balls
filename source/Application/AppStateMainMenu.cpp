#include <Application/AppStateMainMenu.hpp>
#include <Application/AppStateStack.hpp>
#include <Application/AppStateGame.hpp>
#include <Application/AppStateScoreScreen.hpp>
#include <Gui/GuiLabel.hpp>
#include <Gui/GuiButton.hpp>
#include <Utilities/UtilityMethods.hpp>

namespace mnk {

AppStateMainMenu::AppStateMainMenu(AppStateStack& stateStack, Resources& resources) :
    AppState(stateStack, resources),
    mGuiContainer(),
    mWorld(resources) {

    initGui();
    mWorld.initMenu();
    mResources.musicPlayer.play(MusicId::MainMenu);
}

AppStateMainMenu::~AppStateMainMenu() {}

void AppStateMainMenu::update(sf::Time dt) {
    mWorld.update(dt);
}

void AppStateMainMenu::handleInputEvent(const sf::Event& event) {
    mGuiContainer.handleEvent(event);
}

void AppStateMainMenu::handleRealTimeInput() {}

void AppStateMainMenu::render() {
    mWorld.render();
    mResources.renderTarget.draw(mGuiContainer);
}

void AppStateMainMenu::initGui() {
    auto titleLabel = std::make_shared<GuiLabel>("SPACE BALLS", mResources.fontHolder.get(FontId::MenuFont), 32);
    mGuiContainer.addComponent(titleLabel);

    auto playButton = std::make_shared<GuiButton>(
        mResources.textureHolder.get(TextureId::ButtonNormal),
        mResources.textureHolder.get(TextureId::ButtonSelected),
        mResources.textureHolder.get(TextureId::ButtonPressed),
        mResources.fontHolder.get(FontId::MenuFont));
    playButton->setCallback([this](){
        mStateStack.pop();
        mStateStack.push(AppState::Ptr(new AppStateGame(mStateStack, mResources)));
    });
    playButton->setText("PLAY");
    playButton->setSelectedTextColor(sf::Color::Red);
    playButton->setCharacterSize(16);
    playButton->move(titleLabel->getPosition().x,
        titleLabel->getPosition().y + 0.5f * (64.0f + playButton->getLocalBounds().height));
    mGuiContainer.addComponent(playButton);

    auto scoreButton = std::make_shared<GuiButton>(
        mResources.textureHolder.get(TextureId::ButtonNormal),
        mResources.textureHolder.get(TextureId::ButtonSelected),
        mResources.textureHolder.get(TextureId::ButtonPressed),
        mResources.fontHolder.get(FontId::MenuFont));
    scoreButton->setCallback([this](){
        mStateStack.push(AppState::Ptr(new AppStateScoreScreen(mStateStack, mResources)));
    });
    scoreButton->setText("HIGH SCORE");
    scoreButton->setSelectedTextColor(sf::Color::Red);
    scoreButton->setCharacterSize(16);
    scoreButton->move(playButton->getPosition().x,
        playButton->getPosition().y + 0.5f * (playButton->getLocalBounds().height + scoreButton->getLocalBounds().height));
    mGuiContainer.addComponent(scoreButton);

    auto exitButton = std::make_shared<GuiButton>(
        mResources.textureHolder.get(TextureId::ButtonNormal),
        mResources.textureHolder.get(TextureId::ButtonSelected),
        mResources.textureHolder.get(TextureId::ButtonPressed),
        mResources.fontHolder.get(FontId::MenuFont));
    exitButton->setCallback([this](){
        mStateStack.pop();
    });
    exitButton->setText("QUIT");
    exitButton->setSelectedTextColor(sf::Color::Red);
    exitButton->setCharacterSize(16);
    exitButton->move(scoreButton->getPosition().x,
        scoreButton->getPosition().y + 0.5f * (scoreButton->getLocalBounds().height + exitButton->getLocalBounds().height));
    mGuiContainer.addComponent(exitButton);

    mGuiContainer.setPosition(sf::Vector2f(0.5 * mResources.renderTarget.getSize().x, 0.25 * mResources.renderTarget.getSize().y));
}

}
