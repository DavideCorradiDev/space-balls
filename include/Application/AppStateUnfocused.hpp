#ifndef APPSTATEUNFOCUSED_HPP
#define APPSTATEUNFOCUSED_HPP

#include <Application/AppState.hpp>

namespace mnk {

class AppStateUnfocused : public AppState {
public:
    AppStateUnfocused(AppStateStack& stateStack, Resources& resources);
    virtual ~AppStateUnfocused();

    virtual void handleInputEvent(const sf::Event& event);
    virtual void handleRealTimeInput();
    virtual void update(sf::Time dt);
    virtual void render();
};

}

#endif // APPSTATEUNFOCUSED_HPP
