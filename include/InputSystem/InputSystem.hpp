#ifndef INPUTSYSTEM_HPP
#define INPUTSYSTEM_HPP

#include <EntitySystem/GameSystem.hpp>
#include <InputSystem/InputComponent.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>

namespace mnk {

class InputSystem : public GameSystem<InputComponent> {
public:
    virtual ~InputSystem();

    void handleInputEvent(const sf::Event& event);
    void handleRealTimeInput();

private:
    virtual void onUpdateObject(sf::Time dt, InputComponent& object);
    virtual void onUpdateEnd(sf::Time dt);

private:
    std::vector<InputCode> mInputCodes;
};

}

#endif // INPUTSYSTEM_HPP
