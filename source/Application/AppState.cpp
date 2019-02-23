#include <Application/AppState.hpp>
#include <Application/AppStateStack.hpp>

namespace mnk {

AppState::AppState(AppStateStack& stateStack, Resources& resources) :
    mStateStack(stateStack),
    mResources(resources) {}

AppState::~AppState() {}

void AppState::handleInputEvent(const sf::Event& event) {}
void AppState::handleRealTimeInput() {}
void AppState::update(sf::Time dt) {}
void AppState::render() {}

Resources& AppState::getResources() { return mResources; }

}
