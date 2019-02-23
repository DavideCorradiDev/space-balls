#ifndef MSGSETPOSE_HPP
#define MSGSETPOSE_HPP

#include <MessageSystem/Message.hpp>
#include <SFML/System/Vector2.hpp>

namespace mnk {

class MsgSetPose : public Message {
public:
    MsgSetPose(const sf::Vector2f& position, float orientationDeg) :
        position(position),
        orientationDeg(orientationDeg) {}
    virtual ~MsgSetPose() {}

public:
    sf::Vector2f position;
    float orientationDeg;
};

}

#endif // MSGSETPOSE_HPP

