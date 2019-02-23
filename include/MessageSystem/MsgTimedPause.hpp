#ifndef MSGTIMEDPAUSE_HPP
#define MSGTIMEDPAUSE_HPP

#include <MessageSystem/Message.hpp>
#include <SFML/System/Time.hpp>

namespace mnk {

class MsgTimedPause : public Message {
public:
    MsgTimedPause(sf::Time pauseTime) : pauseTime(pauseTime) {}
    virtual ~MsgTimedPause() {}

public:
    sf::Time pauseTime;
};

}

#endif // MSGTIMEDPAUSE_HPP
