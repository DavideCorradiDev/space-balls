#ifndef MSGCMDTURNRIGHT_HPP
#define MSGCMDTURNRIGHT_HPP

#include <MessageSystem/Message.hpp>
#include <SFML/System/Time.hpp>

namespace mnk {

class MsgCmdTurnRight : public Message {
public:
    MsgCmdTurnRight(sf::Time dt) : dt(dt) {}
    ~MsgCmdTurnRight() {};

public:
    sf::Time dt;
};

}

#endif // MSGCMDTURNRIGHT_HPP
