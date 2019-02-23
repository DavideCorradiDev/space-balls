#include <AudioSystem/ACSoundEmitter.hpp>

namespace mnk {

ACSoundEmitter::ACSoundEmitter() :
    AudioComponent(),
    mSound() {}

ACSoundEmitter::ACSoundEmitter(const sf::SoundBuffer& buffer) :
    AudioComponent(),
    mSound(buffer) {}

ACSoundEmitter::ACSoundEmitter(const sf::Sound& sound) :
    AudioComponent(),
    mSound(sound) {}

void ACSoundEmitter::update(sf::Time dt) {}

sf::Sound& ACSoundEmitter::getSound() { return mSound; }

const sf::Sound& ACSoundEmitter::getSound() const { return mSound; }

void ACSoundEmitter::setSound(const sf::Sound& value) { mSound = value; }

}
