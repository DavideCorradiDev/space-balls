#include <AudioSystem/AudioSystem.hpp>

namespace mnk {

AudioSystem::~AudioSystem() {}

void AudioSystem::onUpdateObject(sf::Time dt, AudioComponent& object) {
    object.update(dt);
}

}
