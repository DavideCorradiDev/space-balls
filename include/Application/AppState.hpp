#ifndef STATE_HPP
#define STATE_HPP

#include <ResourceSystem/Resources.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <memory>

namespace mnk {

class AppStateStack;

class AppState {
public:
    typedef std::unique_ptr<AppState> Ptr;

public:
    AppState(AppStateStack& stateStack, Resources& resources);
    virtual ~AppState() = 0;

    virtual void handleInputEvent(const sf::Event& event);
    virtual void handleRealTimeInput();
    virtual void update(sf::Time dt);
    virtual void render();

    Resources& getResources();

protected:
    AppStateStack& mStateStack;
    Resources mResources;
};

}

#endif // STATE_HPP
