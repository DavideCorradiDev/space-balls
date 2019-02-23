#ifndef GCTIMEDLIFE_HPP
#define GCTIMEDLIFE_HPP

#include <GameplaySystem/GameplayComponent.hpp>

namespace mnk {

class GCTimedLife : public GameplayComponent {
public:
    GCTimedLife(sf::Time lifeTime);
    virtual ~GCTimedLife();

    virtual void update(sf::Time dt);

private:
    sf::Time mLifeTime;
    sf::Time mCurrentTime;
};

}

#endif // GCTIMEDLIFE_HPP
