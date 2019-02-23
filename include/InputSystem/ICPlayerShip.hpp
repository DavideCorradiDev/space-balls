#ifndef ICPLAYERSHIP_HPP
#define ICPLAYERSHIP_HPP

#include <InputSystem/InputComponent.hpp>

namespace mnk {

class ICPlayerShip : public InputComponent {
public:
    virtual ~ICPlayerShip();

    virtual void handleInputCode(sf::Time dt, InputCode inputCode);
};

}

#endif // ICPLAYERSHIP_HPP
