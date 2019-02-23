#ifndef SOUNDBUFFERHOLDER_HPP
#define SOUNDBUFFERHOLDER_HPP

#include <ResourceSystem/ResourceHolder.hpp>
#include <SFML/Audio.hpp>

namespace mnk {

enum class SoundBufferId {
    Shoot,
    Explosion,
    Engine,
    NewLife,
    Ufo,
};

typedef ResourceHolder<SoundBufferId, sf::SoundBuffer> SoundBufferHolder;

}

#endif // SOUNDBUFFERHOLDER_HPP
