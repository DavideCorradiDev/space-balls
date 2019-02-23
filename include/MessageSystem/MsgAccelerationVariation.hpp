#ifndef MSGACCELERATIONVARIATION_HPP
#define MSGACCELERATIONVARIATION_HPP

#include <MessageSystem/Message.hpp>

namespace mnk {

class MsgAccelerationVariation : public Message {
public:
    MsgAccelerationVariation(const sf::Vector2f& linear, float angularDeg) :
        linear(linear),
        angularDeg(angularDeg) {}
    virtual ~MsgAccelerationVariation() {}

public:
    sf::Vector2f linear;
    float angularDeg;
};

}

#endif // MSGACCELERATIONVARIATION_HPP
