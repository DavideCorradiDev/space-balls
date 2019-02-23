#ifndef ACSOUNDEMITTER_HPP
#define ACSOUNDEMITTER_HPP

#include <AudioSystem/AudioComponent.hpp>
#include <SFML/Audio/Sound.hpp>

namespace mnk {

class ACSoundEmitter : public AudioComponent {
public:
    ACSoundEmitter();
    ACSoundEmitter(const sf::SoundBuffer& buffer);
    ACSoundEmitter(const sf::Sound& sound);

    virtual void update(sf::Time dt);

    sf::Sound& getSound();
    const sf::Sound& getSound() const;
    void setSound(const sf::Sound& value);

private:
    sf::Sound mSound;
};

}

#endif // ACSOUNDEMITTER_HPP
