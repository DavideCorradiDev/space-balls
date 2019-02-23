#ifndef MSGSETVISIBLE_HPP
#define MSGSETVISIBLE_HPP

#include <MessageSystem/Message.hpp>

namespace mnk {

class MsgSetVisible : public Message {
public:
    MsgSetVisible(bool visible) : visible(visible) {}
    virtual ~MsgSetVisible() {}

public:
    bool visible;
};

}

#endif // MSGSETVISIBLE_HPP
