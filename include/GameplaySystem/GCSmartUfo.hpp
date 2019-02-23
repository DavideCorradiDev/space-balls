#ifndef GCSMARTUFO_HPP
#define GCSMARTUFO_HPP

#include <GameplaySystem/GCUfo.hpp>

namespace mnk {

class GCSmartUfo : public GCUfo {
public:
    GCSmartUfo(EntityFactory& entityFactory, float speed, float reloadTime, float bulletSpeed, EDUfo::Type type, float shootDeviation);
    virtual ~GCSmartUfo();

protected:
    virtual void performMovement(sf::Time dt);
    virtual void attack();

private:
    sf::Vector2f mMovementDirection;
    float mShootDeviation;
};

}

#endif // GCSMARTUFO_HPP
