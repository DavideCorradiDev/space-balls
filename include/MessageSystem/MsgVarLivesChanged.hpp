#ifndef MSGVARLIVESCHANGED_HPP
#define MSGVARLIVESCHANGED_HPP

#include <MessageSystem/Message.hpp>

namespace mnk {

class MsgVarLivesChanged : public Message {
public:
    MsgVarLivesChanged(unsigned int lives) : lives(lives) {}
    virtual ~MsgVarLivesChanged() {}

public:
    unsigned int lives;
};

}

#endif // MSGVARLIVESCHANGED_HPP

