#ifndef AUDIOCOMPONENT_HPP
#define AUDIOCOMPONENT_HPP

#include <EntitySystem/Component.hpp>

namespace mnk {

class AudioComponent : public Component {
public:
    virtual ~AudioComponent() = 0;
    virtual void update(sf::Time dt);
};

}

#endif // AUDIOCOMPONENT_HPP
