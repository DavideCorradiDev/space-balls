#ifndef STATEMAINMENU_HPP
#define STATEMAINMENU_HPP

#include <Application/AppState.hpp>
#include <GameWorld/GameWorld.hpp>
#include <Gui/GuiContainer.hpp>

namespace mnk {

class AppStateMainMenu : public AppState {
public:
    AppStateMainMenu(AppStateStack& stateStack, Resources& resources);
    virtual ~AppStateMainMenu();

    virtual void handleInputEvent(const sf::Event& event);
    virtual void handleRealTimeInput();
    virtual void update(sf::Time dt);
    virtual void render();

private:
    void initGui();

private:
    GuiContainer mGuiContainer;
    GameWorld mWorld;
};

}

#endif // STATEMAINMENU_HPP
