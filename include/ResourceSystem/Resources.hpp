#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include <ResourceSystem/AnimationHolder.hpp>
#include <ResourceSystem/FontHolder.hpp>
#include <ResourceSystem/SoundBufferHolder.hpp>
#include <ResourceSystem/TextureHolder.hpp>
#include <ResourceSystem/MusicPlayer.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace mnk {

struct Resources {
    Resources(sf::RenderTarget& renderTarget, AnimationHolder& animationHolder, FontHolder& fontHolder, MusicPlayer& musicPlayer, SoundBufferHolder& soundBufferHolder, TextureHolder& textureHolder);

    sf::RenderTarget& renderTarget;
    AnimationHolder& animationHolder;
    FontHolder& fontHolder;
    MusicPlayer& musicPlayer;
    SoundBufferHolder& soundBufferHolder;
    TextureHolder& textureHolder;
};

}

#endif // RESOURCES_HPP
