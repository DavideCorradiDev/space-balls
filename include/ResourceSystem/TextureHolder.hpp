#ifndef TEXTUREHOLDER_HPP
#define TEXTUREHOLDER_HPP

#include <ResourceSystem/ResourceHolder.hpp>
#include <SFML/Graphics.hpp>

namespace mnk {

enum class TextureId {
    Ship,
    Bullet,
    SpaceBall,
    Explosion,
    ButtonSelected,
    ButtonNormal,
    ButtonPressed,
    SpaceBackground,
    Ufo,
};

typedef ResourceHolder<TextureId, sf::Texture> TextureHolder;

}

#endif // TEXTUREHOLDER_HPP
