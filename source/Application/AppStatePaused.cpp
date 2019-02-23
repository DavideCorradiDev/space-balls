#include <Application/AppStatePaused.hpp>
#include <Application/AppStateStack.hpp>
#include <Application/AppStateMainMenu.hpp>
#include <Gui/GuiLabel.hpp>
#include <Gui/GuiButton.hpp>
#include <Utilities/UtilityMethods.hpp>

namespace mnk {

AppStatePaused::AppStatePaused(AppStateStack& stateStack, Resources& resources) :
    AppState(stateStack, resources),
    mGuiContainer() {
    initGui();
}

AppStatePaused::~AppStatePaused() {}

void AppStatePaused::handleInputEvent(const sf::Event& event) {
    mGuiContainer.handleEvent(event);
    switch(event.type) {
        case sf::Event::KeyReleased:
            switch(event.key.code) {
            case sf::Keyboard::Escape:
                mStateStack.pop();
            break;
            default:
                break;
            }
            break;
        default:
        break;
    }
}

void AppStatePaused::handleRealTimeInput() {

}

void AppStatePaused::update(sf::Time dt) {

}

void AppStatePaused::render() {
    mResources.renderTarget.draw(mGuiContainer);
}

void AppStatePaused::initGui() {
    auto titleLabel = std::make_shared<GuiLabel>("PAUSED", mResources.fontHolder.get(FontId::MenuFont), 32);
    mGuiContainer.addComponent(titleLabel);

    auto returnToGameButton = std::make_shared<GuiButton>(
        mResources.textureHolder.get(TextureId::ButtonNormal),
        mResources.textureHolder.get(TextureId::ButtonSelected),
        mResources.textureHolder.get(TextureId::ButtonPressed),
        mResources.fontHolder.get(FontId::MenuFont));
    returnToGameButton->setCallback([this](){
        mStateStack.pop();
    });
    returnToGameButton->setText("RETURN TO GAME");
    returnToGameButton->setSelectedTextColor(sf::Color::Red);
    returnToGameButton->setCharacterSize(16);
    returnToGameButton->move(titleLabel->getPosition().x,
        titleLabel->getPosition().y + 0.5f * (64.0f + returnToGameButton->getLocalBounds().height));
    mGuiContainer.addComponent(returnToGameButton);

    auto exitButton = std::make_shared<GuiButton>(
        mResources.textureHolder.get(TextureId::ButtonNormal),
        mResources.textureHolder.get(TextureId::ButtonSelected),
        mResources.textureHolder.get(TextureId::ButtonPressed),
        mResources.fontHolder.get(FontId::MenuFont));
    exitButton->setCallback([this](){
        mStateStack.clear();
        mStateStack.push(AppState::Ptr(new AppStateMainMenu(mStateStack, mResources)));
    });
    exitButton->setText("BACK TO MAIN MENU");
    exitButton->setSelectedTextColor(sf::Color::Red);
    exitButton->setCharacterSize(16);
    exitButton->move(returnToGameButton->getPosition().x,
        returnToGameButton->getPosition().y + 0.5f * (returnToGameButton->getLocalBounds().height + exitButton->getLocalBounds().height));
    mGuiContainer.addComponent(exitButton);

    mGuiContainer.setPosition(sf::Vector2f(0.5 * mResources.renderTarget.getSize().x, 0.25 * mResources.renderTarget.getSize().y));
}

}

