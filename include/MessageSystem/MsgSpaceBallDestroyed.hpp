#ifndef MSGSPACEBALLDESTROYED_HPP
#define MSGSPACEBALLDESTROYED_HPP

#include <MessageSystem/Message.hpp>
#include <EntitySystem/EDSpaceBall.hpp>

namespace mnk {

class MsgSpaceBallDestroyed : public Message {
public:
    MsgSpaceBallDestroyed(EDSpaceBall::Size size) :
        size(size) {}
    virtual ~MsgSpaceBallDestroyed() {}

public:
    EDSpaceBall::Size size;
};

}

#endif // MSGSPACEBALLDESTROYED_HPP

