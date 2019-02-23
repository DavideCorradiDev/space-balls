#include <Application/AppStateScoreScreen.hpp>
#include <Application/AppStateStack.hpp>
#include <Application/AppStateMainMenu.hpp>
#include <GameplaySystem/GSConstants.hpp>
#include <Gui/GuiLabel.hpp>
#include <Gui/GuiButton.hpp>
#include <Gui/GuiScore.hpp>

namespace mnk {

const std::string scoreFile = "./resources/data/data.txt";

AppStateScoreScreen::AppStateScoreScreen(AppStateStack& stateStack, Resources& resources) :
    AppState(stateStack, resources),
    mScoreRecord(GSConstants::NUM_OF_SCORE_ENTRIES),
    mGuiContainer() {

    initGui();
    mScoreRecord.readFromFile(scoreFile);
}

AppStateScoreScreen::AppStateScoreScreen(AppStateStack& stateStack, Resources& resources, ScoreRecord::ScoreEntry newScore) :
    AppState(stateStack, resources),
    mScoreRecord(GSConstants::NUM_OF_SCORE_ENTRIES),
    mGuiContainer() {

    initGui();
    mScoreRecord.readFromFile(scoreFile);
    mScoreRecord.addEntry(newScore);
}

AppStateScoreScreen::~AppStateScoreScreen() {
    mScoreRecord.writeToFile(scoreFile);
}

void AppStateScoreScreen::handleInputEvent(const sf::Event& event) {
    mGuiContainer.handleEvent(event);
}

void AppStateScoreScreen::handleRealTimeInput() {}

void AppStateScoreScreen::update(sf::Time dt) {}

void AppStateScoreScreen::render() {
    mResources.renderTarget.clear();
    mResources.renderTarget.draw(mGuiContainer);
}

void AppStateScoreScreen::initGui() {
    auto titleLabel = std::make_shared<GuiLabel>("HIGH SCORE:", mResources.fontHolder.get(FontId::MenuFont), 32);
    mGuiContainer.addComponent(titleLabel);

    auto score = std::make_shared<GuiScore>(mScoreRecord, mResources.fontHolder.get(FontId::MonospaceFont), 16);
    score->move(titleLabel->getPosition().x,
        titleLabel->getPosition().y + 32.0f);
    mGuiContainer.addComponent(score);

    auto exitButton = std::make_shared<GuiButton>(
        mResources.textureHolder.get(TextureId::ButtonNormal),
        mResources.textureHolder.get(TextureId::ButtonSelected),
        mResources.textureHolder.get(TextureId::ButtonPressed),
        mResources.fontHolder.get(FontId::MenuFont));
    exitButton->setCallback([this](){
        mStateStack.pop();
    });
    exitButton->setText("BACK TO MAIN MENU");
    exitButton->setSelectedTextColor(sf::Color::Red);
    exitButton->setCharacterSize(16);
    exitButton->move(score->getPosition().x,
        score->getPosition().y + score->getLocalBounds().height + 0.5f * (exitButton->getLocalBounds().height));
    mGuiContainer.addComponent(exitButton);

    mGuiContainer.setPosition(sf::Vector2f(0.5 * mResources.renderTarget.getSize().x, 0.25 * mResources.renderTarget.getSize().y));
}

}
