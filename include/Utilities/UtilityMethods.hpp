#ifndef UTILITYMETHODS_HPP
#define UTILITYMETHODS_HPP

#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include <sstream>

namespace mnk {

class AnimatedSprite;

namespace Constants {

const float PI = 4*atan(1.0);

}

void centerOrigin(sf::RectangleShape& shape);
void centerOrigin(sf::CircleShape& shape);
void centerOrigin(sf::Text& text);
void centerOriginX(sf::Text& text);
void centerOrigin(sf::Sprite& sprite);
void centerOrigin(AnimatedSprite& sprite);

float dot(const sf::Vector2f& left, const sf::Vector2f& right);
float norm(const sf::Vector2f& v);
sf::Vector2f normalize(const sf::Vector2f& v);

float deg2rad(float degrees);
sf::Vector2f getOrientationVector(float angleDegrees);

template <typename T>
std::string to_string(const T& n) {
    std::ostringstream stm ;
    stm << n ;
    return stm.str() ;
}

}

#endif // UTILITYMETHODS_HPP
