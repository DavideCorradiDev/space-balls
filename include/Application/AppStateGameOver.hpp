#ifndef APPSTATEGAMEOVER_HPP
#define APPSTATEGAMEOVER_HPP

#include <Application/AppState.hpp>
#include <Gui/GuiContainer.hpp>
#include <Gui/GuiTextBox.hpp>
#include <memory>

namespace mnk {

class AppStateGameOver : public AppState {
public:
    AppStateGameOver(AppStateStack& stateStack, Resources& resources, unsigned int score);
    virtual ~AppStateGameOver();

    virtual void handleInputEvent(const sf::Event& event);
    virtual void handleRealTimeInput();
    virtual void update(sf::Time dt);
    virtual void render();

private:
    void initGui();

private:
    GuiContainer mGuiContainer;
    unsigned int mScore;
    std::shared_ptr<GuiTextBox> mpTextBox;
};

}

#endif // APPSTATEGAMEOVER_HPP
