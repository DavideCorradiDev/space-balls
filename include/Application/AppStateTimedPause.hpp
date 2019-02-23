#ifndef APPSTATETIMEDPAUSE_HPP
#define APPSTATETIMEDPAUSE_HPP

#include <Application/AppState.hpp>
#include <SFML/System/Time.hpp>

namespace mnk {

class AppStateTimedPause : public AppState {
public:
    AppStateTimedPause(AppStateStack& stateStack, Resources& resources, sf::Time pauseTime);
    virtual ~AppStateTimedPause();

    virtual void handleInputEvent(const sf::Event& event);
    virtual void update(sf::Time dt);

private:
    sf::Time mPauseTime;
    sf::Time mCurrentTime;
};

}

#endif // APPSTATETIMEDPAUSE_HPP
