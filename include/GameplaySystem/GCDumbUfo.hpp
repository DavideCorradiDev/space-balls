#ifndef GCDUMBUFO_HPP
#define GCDUMBUFO_HPP

#include <GameplaySystem/GCUfo.hpp>

namespace mnk {

class GCDumbUfo : public GCUfo {
public:
    GCDumbUfo(EntityFactory& entityFactory, float speed, float reloadTime, float bulletSpeed, EDUfo::Type type);
    virtual ~GCDumbUfo();

protected:
    virtual void performMovement(sf::Time dt);
    virtual void attack();

private:
    sf::Vector2f mMovementDirection;
};

}

#endif // GCDUMBUFO_HPP
