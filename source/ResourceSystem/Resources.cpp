#include <ResourceSystem/Resources.hpp>

namespace mnk {

Resources::Resources(sf::RenderTarget& renderTarget, AnimationHolder& animationHolder, FontHolder& fontHolder, MusicPlayer& musicPlayer, SoundBufferHolder& soundBufferHolder, TextureHolder& textureHolder) :
    renderTarget(renderTarget),
    animationHolder(animationHolder),
    fontHolder(fontHolder),
    musicPlayer(musicPlayer),
    soundBufferHolder(soundBufferHolder),
    textureHolder(textureHolder) {}

}
