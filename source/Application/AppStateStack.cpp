#include <Application/AppStateStack.hpp>
#include <cassert>
#include <iostream>

namespace mnk {

AppStateStack::PendingChange::PendingChange(Action action, AppState::Ptr pAppState) :
    action(action),
    pAppState(std::move(pAppState)) {}

AppStateStack::AppStateStack(Resources& resources) :
    mpStates(),
    mPendingChanges(),
    mResources(resources) {}

void AppStateStack::update(sf::Time dt) {
    applyPendingChanges();
    if(!mpStates.empty()) {
        mpStates.back()->update(dt);
    }
}

void AppStateStack::handleInputEvent(const sf::Event& event) {
    if(!mpStates.empty()) {
        mpStates.back()->handleInputEvent(event);
    }
}

void AppStateStack::handleRealTimeInput() {
    if(!mpStates.empty()) {
        mpStates.back()->handleRealTimeInput();
    }
}

void AppStateStack::render() {
    for(unsigned i = 0; i < mpStates.size(); i++) {
        mpStates[i]->render();
    }
}

bool AppStateStack::empty() const {
    return mpStates.empty();
}

void AppStateStack::push(AppState::Ptr pAppState) {
    mPendingChanges.push_back(PendingChange(Action::Push, std::move(pAppState)));
}

void AppStateStack::pop() {
    mPendingChanges.push_back(PendingChange(Action::Pop));
}

void AppStateStack::clear() {
    mPendingChanges.push_back(PendingChange(Action::Clear));
}

void AppStateStack::applyPendingChanges() {
    for(PendingChange& pendingChange : mPendingChanges) {
        switch(pendingChange.action) {
        case Action::Push:
            assert(pendingChange.pAppState);
            mpStates.push_back(std::move(pendingChange.pAppState));
            break;
        case Action::Pop:
            assert(!mpStates.empty());
            mpStates.pop_back();
            break;
        case Action::Clear:
            mpStates.clear();
            break;
        }
    }
    mPendingChanges.clear();
}

}
