#ifndef ACSOUNDPLAYER_HPP
#define ACSOUNDPLAYER_HPP

#include <AudioSystem/AudioComponent.hpp>
#include <ResourceSystem/SoundBufferHolder.hpp>
#include <SFML/Audio/Sound.hpp>
#include <list>

namespace mnk {

class ACSoundPlayer : public AudioComponent {
public:
    ACSoundPlayer(SoundBufferHolder& soundBufferHolder);
    virtual ~ACSoundPlayer();
    virtual void update(sf::Time dt);

    virtual bool isDeleted() const;

private:
    void playSound(SoundBufferId soundId);

private:
    SoundBufferHolder& mSoundBufferHolder;
    std::list<sf::Sound> mSounds;
};

}

#endif // ACSOUNDPLAYER_HPP
