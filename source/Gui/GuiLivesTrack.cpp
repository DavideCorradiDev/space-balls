#include <Gui/GuiLivesTrack.hpp>
#include <Utilities/UtilityMethods.hpp>

namespace mnk {

GuiLivesTrack::GuiLivesTrack(unsigned int lives, const sf::Texture& livesIcon, const sf::IntRect& rectangle) :
    GuiComponent(false),
    mLives(lives),
    mLivesIconSprite(livesIcon, rectangle) {
}

void GuiLivesTrack::handleEvent(const sf::Event& event) {}

unsigned int GuiLivesTrack::getLives() const { return mLives; }
void GuiLivesTrack::setLives(unsigned int value) { mLives = value; }

void GuiLivesTrack::setIconRotation(float valueDeg) {
    mLivesIconSprite.setRotation(valueDeg);
}

void GuiLivesTrack::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    for(unsigned int i = 0; i < mLives; i++) {
        target.draw(mLivesIconSprite, states);
        states.transform.translate(mLivesIconSprite.getLocalBounds().width, 0.0f);
    }
}

}
