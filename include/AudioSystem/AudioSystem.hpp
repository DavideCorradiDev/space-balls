#ifndef AUDIOSYSTEM_HPP
#define AUDIOSYSTEM_HPP

#include <EntitySystem/GameSystem.hpp>
#include <AudioSystem/AudioComponent.hpp>
#include <SFML/System/Time.hpp>

namespace mnk {

class AudioSystem : public GameSystem<AudioComponent> {
public:
    virtual ~AudioSystem();

private:
    virtual void onUpdateObject(sf::Time dt, AudioComponent& object);
};

}

#endif // AUDIOSYSTEM_HPP
