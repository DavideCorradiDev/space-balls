#ifndef MSGCONTACTSHIP_HPP
#define MSGCONTACTSHIP_HPP

#include <MessageSystem/Message.hpp>

namespace mnk {

class MsgContactShip : public Message {
public:
    MsgContactShip(bool isPlayer) :
        isPlayer(isPlayer) {}
    virtual ~MsgContactShip() {}

public:
    bool isPlayer;
};

}

#endif // MSGCONTACTSHIP_HPP
