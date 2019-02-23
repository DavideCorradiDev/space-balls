#ifndef APPSTATEMENUBACKGROUND_HPP
#define APPSTATEMENUBACKGROUND_HPP

#include <Application/AppState.hpp>
#include <GameWorld/GameWorld.hpp>

namespace mnk {

class AppStateMenuBackground : public AppState {
public:
    AppStateMenuBackground(AppStateStack& stateStack, Resources& resources);
    virtual ~AppStateMenuBackground();

    virtual void handleInputEvent(const sf::Event& event);
    virtual void handleRealTimeInput();
    virtual void update(sf::Time dt);
    virtual void render();

private:
    GameWorld mWorld;
};

}

#endif // APPSTATEMENUBACKGROUND_HPP
