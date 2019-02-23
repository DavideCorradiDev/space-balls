#ifndef APPSTATEPAUSED_HPP
#define APPSTATEPAUSED_HPP

#include <Application/AppState.hpp>
#include <Gui/GuiContainer.hpp>

namespace mnk {

class AppStatePaused : public AppState {
public:
    AppStatePaused(AppStateStack& stateStack, Resources& resources);
    virtual ~AppStatePaused();

    virtual void handleInputEvent(const sf::Event& event);
    virtual void handleRealTimeInput();
    virtual void update(sf::Time dt);
    virtual void render();

private:
    void initGui();

private:
    GuiContainer mGuiContainer;
};

}

#endif // APPSTATEPAUSED_HPP
