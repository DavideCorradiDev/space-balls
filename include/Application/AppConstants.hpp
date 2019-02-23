#ifndef APPCONSTANTS_HPP
#define APPCONSTANTS_HPP

#include <SFML/System/String.hpp>
#include <ResourceSystem/FontHolder.hpp>

namespace mnk {

namespace AppConstants {

#ifndef NDEBUG
const sf::Uint32 WINDOW_STYLE = sf::Style::Titlebar | sf::Style::Close;
#else
const sf::Uint32 WINDOW_STYLE = sf::Style::Titlebar;
#endif
const float UPDATE_TIME = 1.0f / 60.0f;
const float RENDER_TIME = 1.0f / 60.0f;
const int DISPLAY_WIDTH = 800;
const int DISPLAY_HEIGHT = 600;
const int DISPLAY_BITSPERPIXEL = 32;
const sf::String APPLICATION_NAME = "Space Balls";
const sf::String BEVELED_PIXEL_PATH = "./resources/bitmap/beveledpixel.png";
#ifndef NDEBUG
const float FPS_SIZE = 10.0f;
const FontId FPS_FONT = FontId::MenuFont;
#endif

}

}

#endif // APPCONSTANTS_HPP
