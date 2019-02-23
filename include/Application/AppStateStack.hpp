#ifndef STATESTACK_HPP
#define STATESTACK_HPP

#include <Utilities/NonCopyable.hpp>
#include <Application/AppState.hpp>
#include <ResourceSystem/Resources.hpp>
#include <vector>

namespace mnk {

class AppStateStack : public NonCopyable {
public:
    AppStateStack(Resources& resources);

    void handleInputEvent(const sf::Event& event);
    void handleRealTimeInput();
    void update(sf::Time dt);
    void render();

    bool empty() const;
    void push(AppState::Ptr pAppState);     // By value because AppStateStack takes ownership of the pointer.
    void pop();
    void clear();

private:
    enum class Action {
        Push,
        Pop,
        Clear,
    };

    struct PendingChange {
        PendingChange(Action action, AppState::Ptr pAppState = nullptr);
        Action action;
        AppState::Ptr pAppState;
    };

private:
    void applyPendingChanges();

private:
    std::vector<AppState::Ptr> mpStates;
    std::vector<PendingChange> mPendingChanges;
    Resources mResources;
};

}

#endif // STATESTACK_HPP
