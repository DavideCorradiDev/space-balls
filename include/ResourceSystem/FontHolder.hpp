#ifndef FONTHOLDER_HPP
#define FONTHOLDER_HPP

#include <ResourceSystem/ResourceHolder.hpp>
#include <SFML/Graphics.hpp>

namespace mnk {

enum class FontId {
    MenuFont,
    MonospaceFont,
};

typedef ResourceHolder<FontId, sf::Font> FontHolder;

}

#endif // FONTHOLDER_HPP
