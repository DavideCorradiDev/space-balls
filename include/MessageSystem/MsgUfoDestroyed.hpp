#ifndef MSGUFODESTROYED_HPP
#define MSGUFODESTROYED_HPP

#include <MessageSystem/Message.hpp>
#include <EntitySystem/EDUfo.hpp>

namespace mnk {

class MsgUfoDestroyed : public Message {
public:
    MsgUfoDestroyed(EDUfo::Type type) : type(type) {}
    virtual ~MsgUfoDestroyed() {}

public:
    EDUfo::Type type;
};

}

#endif // MSGUFODESTROYED_HPP
