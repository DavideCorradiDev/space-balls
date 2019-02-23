#ifndef GUILABEL_HPP
#define GUILABEL_HPP

#include <Gui/GuiComponent.hpp>
#include <string>

namespace mnk {

class GuiLabel : public GuiComponent {
public:
    GuiLabel(const std::string& text, const sf::Font& font, unsigned int size);

    virtual void handleEvent(const sf::Event& event);

    void setText(const std::string& text);
    void setFont(const sf::Font& font);
    void setCharacterSize(unsigned int size);
    void setTextColor(const sf::Color& color);

    sf::FloatRect getLocalBounds() const;
    const sf::Text& getText() const;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    sf::Text mText;
};

}

#endif // GUILABEL_HPP
