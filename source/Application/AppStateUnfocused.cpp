#include <Application/AppStateUnfocused.hpp>

namespace mnk {

AppStateUnfocused::AppStateUnfocused(AppStateStack& stateStack, Resources& resources) :
    AppState(stateStack, resources) {
}

AppStateUnfocused::~AppStateUnfocused() {}

void AppStateUnfocused::handleInputEvent(const sf::Event& event) {

}

void AppStateUnfocused::handleRealTimeInput() {

}

void AppStateUnfocused::update(sf::Time dt) {

}

void AppStateUnfocused::render() {

}

}
