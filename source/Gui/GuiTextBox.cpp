#include <Gui/GuiTextBox.hpp>
#include <Utilities/UtilityMethods.hpp>

namespace mnk {

GuiTextBox::GuiTextBox(std::size_t textLength, const sf::Font& font, unsigned int characterSize) :
    GuiComponent(true),
    mTextLength(textLength),
    mString(),
    mText(mString, font, characterSize) {
    centerOriginX(mText);
}

void GuiTextBox::handleEvent(const sf::Event& event) {
    switch(event.type) {
    case sf::Event::KeyReleased:
        switch(event.key.code) {
        case sf::Keyboard::Key::Return:
            deactivate();
            break;
        default:
            break;
        }
        break;
    case sf::Event::TextEntered:
        if(event.text.unicode == '\b') {
            if(mText.getString().getSize() > 0) {
                mString.erase(mString.getSize()-1);
            }
        } else if((event.text.unicode >= 'a' && event.text.unicode <= 'z')
            || (event.text.unicode >= 'A' && event.text.unicode <= 'Z')
            || (event.text.unicode >= '0' && event.text.unicode <= '9')) {
            if(mText.getString().getSize() <=  mTextLength) {
                    mString += event.text.unicode;
                }
        }
        break;
    default:
        break;
    }
    mText.setString(mString);
    centerOriginX(mText);
}

const sf::String& GuiTextBox::getString() const { return mString; }

void GuiTextBox::setString(const sf::String& value){
    mString = value;
    mText.setString(mString);
    centerOriginX(mText);
}

const sf::Font* GuiTextBox::getFont() const { return mText.getFont(); }
void GuiTextBox::setFont(const sf::Font& value) { mText.setFont(value); }
unsigned int GuiTextBox::getCharacterSize() const { return mText.getCharacterSize(); }
void GuiTextBox::setCharacterSize(unsigned int value) { mText.setCharacterSize(value); }
const sf::Color& GuiTextBox::getTextColor() const { return mText.getColor(); }
void GuiTextBox::setTextColor(const sf::Color& value) { mText.setColor(value); }

sf::FloatRect GuiTextBox::getLocalBounds() const {
    return mText.getLocalBounds();
}

void GuiTextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(mText, states);
}

}
