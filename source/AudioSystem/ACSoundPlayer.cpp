#include <AudioSystem/ACSoundPlayer.hpp>
#include <MessageSystem/MsgPlaySound.hpp>

namespace mnk {

ACSoundPlayer::ACSoundPlayer(SoundBufferHolder& soundBufferHolder) :
    AudioComponent(),
    mSoundBufferHolder(soundBufferHolder),
    mSounds() {
    addCallback<MsgPlaySound>([this](const MsgPlaySound& message) {
        playSound(message.soundId);
    });
}

ACSoundPlayer::~ACSoundPlayer() {}

void ACSoundPlayer::update(sf::Time dt) {
    mSounds.remove_if([] (const sf::Sound& s) {
        return s.getStatus() == sf::Sound::Stopped;
    });
}

bool ACSoundPlayer::isDeleted() const {
    return Component::isDeleted() && mSounds.empty();
}

void ACSoundPlayer::playSound(SoundBufferId soundId) {
    mSounds.push_back(sf::Sound(mSoundBufferHolder.get(soundId)));
    mSounds.back().play();
}

}
