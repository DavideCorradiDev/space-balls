#ifndef GUILIVESTRACK_HPP
#define GUILIVESTRACK_HPP

#include <Gui/GuiComponent.hpp>

namespace mnk {

class GuiLivesTrack : public GuiComponent {
public:
    GuiLivesTrack(unsigned int lives, const sf::Texture& livesIcon, const sf::IntRect& rectangle);

    virtual void handleEvent(const sf::Event& event);

    unsigned int getLives() const;
    void setLives(unsigned int value);
    void setIconRotation(float valueDeg);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    unsigned int mLives;
    sf::Sprite mLivesIconSprite;
};

}

#endif // GUILIVESTRACK_HPP
