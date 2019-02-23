#ifndef RCSPRITE_HPP
#define RCSPRITE_HPP

#include <RenderSystem/RenderComponent.hpp>

namespace mnk {

class RCSprite : public RenderComponent {
public:
    RCSprite();
    RCSprite(const sf::Texture& texture);
    RCSprite(const sf::Texture& texture, const sf::IntRect& rectangle);

    sf::Sprite& getSprite();
    const sf::Sprite& getSprite() const;
    void setSprite(const sf::Sprite& value);

protected:
    virtual void onDraw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    sf::Sprite mSprite;
};

}

#endif // RCSPRITE_HPP
