#ifndef INPUTCOMPONENT_HPP
#define INPUTCOMPONENT_HPP

#include <EntitySystem/Component.hpp>
#include <InputSystem/InputCode.hpp>

namespace mnk {

class InputComponent : public Component {
public:
    virtual ~InputComponent() = 0;

    virtual void handleInputCode(sf::Time dt, InputCode inputCode);
};

}

#endif // INPUTCOMPONENT_HPP
