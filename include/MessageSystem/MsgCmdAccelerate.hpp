#ifndef MSGGCMDACCELERATE_HPP
#define MSGCMDACCELERATE_HPP

#include <MessageSystem/Message.hpp>
#include <SFML/System/Time.hpp>

namespace mnk {

class MsgCmdAccelerate : public Message {
public:
    virtual ~MsgCmdAccelerate() {}
};

}

#endif // MSGGCMDACCELERATE_HPP
