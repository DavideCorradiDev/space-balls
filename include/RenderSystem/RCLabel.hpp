#ifndef RCLABEL_HPP
#define RCLABEL_HPP

#include <RenderSystem/RenderComponent.hpp>

namespace mnk {

class RCLabel : public RenderComponent {
public:
    RCLabel();
    RCLabel(const sf::String& string, const sf::Font& font, unsigned int characterSize = 30);
    virtual ~RCLabel();

    //sf::Text& getText();
    const sf::Text& getText() const;
    void setText(const sf::Text& value);

protected:
    virtual void onDraw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    sf::Text mText;
};

}

#endif // RCLABEL_HPP
