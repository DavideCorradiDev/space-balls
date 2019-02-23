#ifndef MSGSHIPPOSITION_HPP
#define MSGSHIPPOSITION_HPP

#include <MessageSystem/Message.hpp>
#include <SFML/System/Vector2.hpp>

namespace mnk {

class MsgShipPosition : public Message {
public:
    MsgShipPosition(const sf::Vector2f& position) :
        position(position) {}
    virtual ~MsgShipPosition() {}

public:
    sf::Vector2f position;
};

}

#endif // MSGSHIPPOSITION_HPP
