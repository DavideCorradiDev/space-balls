#ifndef GAMEPLAYCOMPONENT_HPP
#define GAMEPLAYCOMPONENT_HPP

#include <EntitySystem/Component.hpp>

namespace mnk {

class GameplayComponent : public Component {
public:
    virtual ~GameplayComponent();

    virtual void update(sf::Time dt);
};

}

#endif // GAMEPLAYCOMPONENT_HPP
