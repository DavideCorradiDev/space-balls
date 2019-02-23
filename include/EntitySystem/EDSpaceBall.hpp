#ifndef EDSPACEBALL_HPP
#define EDSPACEBALL_HPP

#include <EntitySystem/EntityData.hpp>
#include <SFML/System/Vector2.hpp>

namespace mnk {

class EDSpaceBall : public EntityData {
public:
    enum class Size {
        Big,
        Medium,
        Small,
    };

public:
    EDSpaceBall(Size size, const sf::Vector2f& moveDirection) :
        size(size),
        moveDirection(moveDirection) {}
    virtual ~EDSpaceBall() {}

public:
    Size size;
    sf::Vector2f moveDirection;
};

}

#endif // EDSPACEBALL_HPP
