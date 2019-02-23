#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <vector>
#include <string>

namespace mnk {

class Animation {
public:
    Animation();
    Animation(const sf::Texture& texture);

    const sf::Texture* getpTexture() const;
    void setTexture(const sf::Texture& texture);

    const sf::IntRect& getFrame(unsigned int index) const;
    void addFrame(const sf::IntRect& frame);

    std::size_t getNumberOfFrames() const;

private:
    const sf::Texture* mpTexture;
    std::vector<sf::IntRect> mFrames;
};

}

#endif // ANIMATION_HPP
