#ifndef MSGPOSEDISPLACEMENT_HPP
#define MSGPOSEDISPLACEMENT_HPP

#include <MessageSystem/Message.hpp>
#include <SFML/System/Vector2.hpp>

namespace mnk {

class MsgPoseDisplacement : public Message {
public:
    MsgPoseDisplacement(const sf::Vector2f& translation, float rotationDeg) :
        translation(translation),
        rotationDeg(rotationDeg) {}
    virtual ~MsgPoseDisplacement() {}

public:
    sf::Vector2f translation;
    float rotationDeg;
};

}

#endif // MSGPOSEDISPLACEMENT_HPP
