#include <Gui/GuiLabel.hpp>
#include <Utilities/UtilityMethods.hpp>

namespace mnk {

GuiLabel::GuiLabel(const std::string& text, const sf::Font& font, unsigned int size) :
    GuiComponent(false),
    mText(text, font, size) {
    centerOrigin(mText);
}

void GuiLabel::handleEvent(const sf::Event& event) {}

void GuiLabel::setText(const std::string& text) {
    mText.setString(text);
    centerOrigin(mText);
}

void GuiLabel::setFont(const sf::Font& font) {
    mText.setFont(font);
    centerOrigin(mText);
}

void GuiLabel::setCharacterSize(unsigned int size) {
    mText.setCharacterSize(size);
    centerOrigin(mText);
}

void GuiLabel::setTextColor(const sf::Color& color) {
    mText.setColor(color);
}

void GuiLabel::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(mText, states);
}


sf::FloatRect GuiLabel::getLocalBounds() const {
    return mText.getLocalBounds();
}

const sf::Text& GuiLabel::getText() const { return mText; }

}
