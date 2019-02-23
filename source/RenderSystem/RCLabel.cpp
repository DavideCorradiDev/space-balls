#include <RenderSystem/RCLabel.hpp>
#include <Utilities/UtilityMethods.hpp>

namespace mnk {

RCLabel::RCLabel() :
    RenderComponent(),
    mText() {
    centerOrigin(mText);
}

RCLabel::RCLabel(const sf::String& string, const sf::Font& font, unsigned int characterSize) :
    RenderComponent(),
    mText(string, font, characterSize) {
    centerOrigin(mText);
}

RCLabel::~RCLabel() {}

//sf::Text& RCLabel::getText() { return mText; }
const sf::Text& RCLabel::getText() const { return mText; }
void RCLabel::setText(const sf::Text& value) {
    mText = value;
    centerOrigin(mText);
}

void RCLabel::onDraw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(mText, states);
}

}
