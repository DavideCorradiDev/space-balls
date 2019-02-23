#ifndef MSGVELOCITYVARIATION_HPP
#define MSGVELOCITYVARIATION_HPP

#include <MessageSystem/Message.hpp>

namespace mnk {

class MsgVelocityVariation : public Message {
public:
    MsgVelocityVariation(const sf::Vector2f& linear, float angularDeg) :
        linear(linear),
        angularDeg(angularDeg) {}
    virtual ~MsgVelocityVariation() {}

public:
    sf::Vector2f linear;
    float angularDeg;
};

}

#endif // MSGVELOCITYVARIATION_HPP
