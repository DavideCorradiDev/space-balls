#include <InputSystem/InputSystem.hpp>

namespace mnk {

InputSystem::~InputSystem() {}

void InputSystem::handleInputEvent(const sf::Event& event) {
    switch(event.type) {
    case sf::Event::EventType::KeyPressed:
        switch(event.key.code) {
        case sf::Keyboard::Key::Up:
            mInputCodes.push_back(InputCode::Accelerate);
            break;
        default:
            break;
        }
        break;
    case sf::Event::EventType::KeyReleased:
        switch(event.key.code) {
        case sf::Keyboard::Key::Up:
            mInputCodes.push_back(InputCode::Stop);
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}

void InputSystem::handleRealTimeInput() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        mInputCodes.push_back(InputCode::TurnLeft);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        mInputCodes.push_back(InputCode::TurnRight);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        mInputCodes.push_back(InputCode::Attack);
    }
}

void InputSystem::onUpdateObject(sf::Time dt, InputComponent& object) {
    for(InputCode inputCode : mInputCodes) {
        object.handleInputCode(dt, inputCode);
    }
}

void InputSystem::onUpdateEnd(sf::Time dt) {
    mInputCodes.clear();
}

}
