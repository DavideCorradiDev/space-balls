#include <Application/AppStateMenuBackground.hpp>

namespace mnk {

AppStateMenuBackground::AppStateMenuBackground(AppStateStack& stateStack, Resources& resources) :
    AppState(stateStack, resources),
    mWorld(resources) {

    mWorld.initMenu();
}

AppStateMenuBackground::~AppStateMenuBackground() {}

void AppStateMenuBackground::handleInputEvent(const sf::Event& event) {
    mWorld.handleInputEvent(event);
}

void AppStateMenuBackground::handleRealTimeInput() {
    mWorld.handleRealTimeInput();
}

void AppStateMenuBackground::update(sf::Time dt) {
    mWorld.update(dt);
}
void AppStateMenuBackground::render() {
    mWorld.render();
}

}
