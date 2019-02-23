#ifndef EDSPAWNER_HPP
#define EDSPAWNER_HPP

#include <EntitySystem/EDSpawner.hpp>
#include <SFML/System/Vector2.hpp>

namespace mnk {

class EDSpawner : public EntityData {
public:
    EDSpawner(const sf::Vector2f& worldSize) :
        worldSize(worldSize) {}
    virtual ~EDSpawner() {}

public:
    sf::Vector2f worldSize;
};

}

#endif // EDSPAWNER_HPP
