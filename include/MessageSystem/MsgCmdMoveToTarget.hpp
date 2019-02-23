#ifndef MSGCMDMOVETOTARGET_HPP
#define MSGCMDMOVETOTARGET_HPP

#include <MessageSystem/Message.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>

namespace mnk {

class MsgCmdMoveToTarget : public Message {
public:
    MsgCmdMoveToTarget(sf::Time dt, const sf::Vector2f& targetPosition) :
        dt(dt),
        targetPosition(targetPosition) {}
    virtual ~MsgCmdMoveToTarget() {}

public:
    sf::Time dt;
    sf::Vector2f targetPosition;
};

}

#endif // MSGCMDMOVETOTARGET_HPP
