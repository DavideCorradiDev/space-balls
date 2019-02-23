#include <Utilities/UtilityMethods.hpp>
#include <ResourceSystem/AnimatedSprite.hpp>
#include <cmath>

namespace mnk {

void centerOrigin(sf::RectangleShape& shape) {
    shape.setOrigin(sf::Vector2f(std::floor(shape.getSize().x * 0.5f), std::floor(shape.getSize().y * 0.5f)));
}

void centerOrigin(sf::CircleShape& shape) {
    shape.setOrigin(sf::Vector2f(shape.getRadius(), shape.getRadius()));
}

void centerOrigin(sf::Text& text) {
//    text.setOrigin(sf::Vector2f(std::floor(text.getLocalBounds().width * 0.5f), std::floor(text.getLocalBounds().height * 0.5f + static_cast<float>(text.getCharacterSize()) * 32.0f / 100.0f)));
    // The local bounds origin is not 0,0 with the text!
    // Because of this an offset must be added when centering the text.
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(sf::Vector2f(
        std::floor(bounds.left + bounds.width * 0.5f),
        std::floor(bounds.top + bounds.height * 0.5f)));
}

void centerOriginX(sf::Text& text) {
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(sf::Vector2f(
        std::floor(bounds.left + bounds.width * 0.5f),
        text.getOrigin().y));
}

void centerOrigin(sf::Sprite& sprite) {
    sprite.setOrigin(sf::Vector2f(std::floor(sprite.getLocalBounds().width * 0.5f), std::floor(sprite.getLocalBounds().height * 0.5f)));
}

void centerOrigin(AnimatedSprite& sprite) {
    sprite.setOrigin(sf::Vector2f(std::floor(sprite.getLocalBounds().width * 0.5f), std::floor(sprite.getLocalBounds().height * 0.5f)));
}

float dot(const sf::Vector2f& left, const sf::Vector2f& right) {
    return (left.x * right.x + left.y * right.y);
}

float norm(const sf::Vector2f& v) {
    return sqrt(dot(v,v));
}

sf::Vector2f normalize(const sf::Vector2f& v) {
    return v / norm(v);
}

float deg2rad(float degrees) {
    return degrees * Constants::PI / 180.0f;
}

sf::Vector2f getOrientationVector(float angleDegrees) {
    float angleRad = deg2rad(angleDegrees);
    return sf::Vector2f(std::cos(angleRad), std::sin(angleRad));
}

}
