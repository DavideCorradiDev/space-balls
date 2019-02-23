#ifndef MSGCONTACTBULLET_HPP
#define MSGCONTACTBULLET_HPP

#include <MessageSystem/Message.hpp>

namespace mnk {

class MsgContactBullet : public Message {
public:
    MsgContactBullet(bool ofPlayer) :
        ofPlayer(ofPlayer) {}
    virtual ~MsgContactBullet() {}

public:
    bool ofPlayer;
};

}

#endif // MSGCONTACTBULLET_HPP
