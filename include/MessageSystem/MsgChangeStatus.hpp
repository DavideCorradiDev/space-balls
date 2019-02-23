#ifndef MSGCHANGESTATUS_HPP
#define MSGCHANGESTATUS_HPP

#include <MessageSystem/Message.hpp>
#include <EntitySystem/GameObject.hpp>

namespace mnk {

class MsgChangeStatus : public Message {
public:
    MsgChangeStatus(GameObject::Status status) :
        status(status) {}
    virtual ~MsgChangeStatus() {}

public:
    GameObject::Status status;
};

}

#endif // MSGCHANGESTATUS_H
