#include <Application/AppStateGameOver.hpp>
#include <Application/AppStateScoreScreen.hpp>
#include <Application/AppStateMainMenu.hpp>
#include <Application/AppStateStack.hpp>
#include <Gui/GuiLabel.hpp>
#include <Gui/GuiButton.hpp>
#include <Gui/GuiTextBox.hpp>
#include <Utilities/UtilityMethods.hpp>
#include <GameplaySystem/GSConstants.hpp>
#include <string>

namespace mnk {

AppStateGameOver::AppStateGameOver(AppStateStack& stateStack, Resources& resources, unsigned int score) :
    AppState(stateStack, resources),
    mGuiContainer(),
    mScore(score),
    mpTextBox(nullptr) {
    initGui();
}

AppStateGameOver::~AppStateGameOver() {}

void AppStateGameOver::handleInputEvent(const sf::Event& event) {
    mGuiContainer.handleEvent(event);
}

void AppStateGameOver::handleRealTimeInput() {}

void AppStateGameOver::update(sf::Time dt) {
    if(!mpTextBox || !mpTextBox->isActive()) {
        mStateStack.clear();
        mStateStack.push(AppState::Ptr(new AppStateMainMenu(mStateStack, mResources)));
        mStateStack.push(AppState::Ptr(new AppStateScoreScreen(mStateStack, mResources, ScoreRecord::ScoreEntry(mpTextBox->getString(), mScore))));
    }
}

void AppStateGameOver::render() {
    mResources.renderTarget.draw(mGuiContainer);
}

void AppStateGameOver::initGui() {
    auto titleLabel = std::make_shared<GuiLabel>("GAME OVER", mResources.fontHolder.get(FontId::MenuFont), 32);
    mGuiContainer.addComponent(titleLabel);

    std::ostringstream stringStream;
    stringStream << "YOUR SCORE: " << mScore;
    auto scoreLabel = std::make_shared<GuiLabel>(stringStream.str(), mResources.fontHolder.get(FontId::MenuFont), 16);
    scoreLabel->move(titleLabel->getPosition().x,
        titleLabel->getPosition().y + 0.5f * (64.0f + scoreLabel->getLocalBounds().height));
    mGuiContainer.addComponent(scoreLabel);

    auto instructionLabel = std::make_shared<GuiLabel>("Insert your name (max 6 characters):", mResources.fontHolder.get(FontId::MenuFont), 16);
    instructionLabel->move(scoreLabel->getPosition().x,
        scoreLabel->getPosition().y + 0.5f * (64.0f + instructionLabel->getLocalBounds().height));
    mGuiContainer.addComponent(instructionLabel);

    mpTextBox = std::make_shared<GuiTextBox>(GSConstants::NUM_OF_CHARS_OF_SCORE_ENTRIES, mResources.fontHolder.get(FontId::MonospaceFont), 16);
    mpTextBox->move(instructionLabel->getPosition().x,
        instructionLabel->getPosition().y + 0.5f * (64.0f + mpTextBox->getLocalBounds().height));
    mpTextBox->activate();
    mGuiContainer.addComponent(mpTextBox);

    mGuiContainer.setPosition(sf::Vector2f(0.5 * mResources.renderTarget.getSize().x, 0.25 * mResources.renderTarget.getSize().y));
}

}
