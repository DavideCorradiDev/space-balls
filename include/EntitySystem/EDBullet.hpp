#ifndef EDBULLET_HPP
#define EDBULLET_HPP

#include <EntitySystem/EntityData.hpp>
#include <ResourceSystem/TextureHolder.hpp>
#include <SFML/System/Vector2.hpp>

namespace mnk {

class EDBullet : public EntityData {
public:
    EDBullet(const sf::Vector2f& velocity, bool ofPlayer) :
        velocity(velocity),
        ofPlayer(ofPlayer) {}
    virtual ~EDBullet() {}

public:
    sf::Vector2f velocity;
    bool ofPlayer;
};

}

#endif // EDBULLET_HPP
