#include <Application/AppStateTimedPause.hpp>
#include <Application/AppStateStack.hpp>
#include <Application/AppStatePaused.hpp>
#include <Gui/GuiLabel.hpp>
#include <Utilities/UtilityMethods.hpp>

namespace mnk {

AppStateTimedPause::AppStateTimedPause(AppStateStack& stateStack, Resources& resources, sf::Time pauseTime) :
    AppState(stateStack, resources),
    mPauseTime(pauseTime),
    mCurrentTime(sf::seconds(0.0f)) {}

AppStateTimedPause::~AppStateTimedPause() {}

void AppStateTimedPause::handleInputEvent(const sf::Event& event) {
    switch(event.type) {
    case(sf::Event::EventType::KeyReleased):
        switch(event.key.code) {
        case sf::Keyboard::Key::Escape:
            mStateStack.push(AppState::Ptr(new AppStatePaused(mStateStack, mResources)));
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}

void AppStateTimedPause::update(sf::Time dt) {
    mCurrentTime += dt;
    if(mCurrentTime >= mPauseTime) {
        mStateStack.pop();
    }
}

}


