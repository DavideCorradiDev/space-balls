#ifndef GUITEXTBOX_HPP
#define GUITEXTBOX_HPP

#include <Gui/GuiComponent.hpp>
#include <string>

namespace mnk {

class GuiTextBox : public GuiComponent {
public:
    GuiTextBox(std::size_t textLength, const sf::Font& font, unsigned int characterSize = 30);

    virtual void handleEvent(const sf::Event& event);

    const sf::String& getString() const;
    void setString(const sf::String& value);
    const sf::Font* getFont() const;
    void setFont(const sf::Font& value);
    unsigned int getCharacterSize() const;
    void setCharacterSize(unsigned int value);
    const sf::Color& getTextColor() const;
    void setTextColor(const sf::Color& value);

    sf::FloatRect getLocalBounds() const;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    std::size_t mTextLength;
    sf::String mString;
    sf::Text mText;
};

}

#endif // GUITEXTBOX_HPP
