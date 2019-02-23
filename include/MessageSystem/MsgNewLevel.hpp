#ifndef MSGNEWLEVEL_HPP
#define MSGNEWLEVEL_HPP

#include <MessageSystem/Message.hpp>

namespace mnk {

class MsgNewLevel : public Message {
public:
    MsgNewLevel() {}
    virtual ~MsgNewLevel() {}
};

}

#endif // MSGNEWLEVEL_HPP
