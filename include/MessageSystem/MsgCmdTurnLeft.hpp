#ifndef MSGCMDTURNLEFT_HPP
#define MSGCMDTURNLEFT_HPP

#include <MessageSystem/Message.hpp>
#include <SFML/System/Time.hpp>

namespace mnk {

class MsgCmdTurnLeft : public Message {
public:
    MsgCmdTurnLeft(sf::Time dt) : dt(dt) {}
    ~MsgCmdTurnLeft() {};

public:
    sf::Time dt;
};

}

#endif // MSGCMDTURNLEFT_HPP
