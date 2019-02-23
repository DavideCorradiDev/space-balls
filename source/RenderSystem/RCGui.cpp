#include <RenderSystem/RCGui.hpp>
#include <Utilities/UtilityMethods.hpp>

namespace mnk {

RCGui::RCGui(const sf::Vector2f& screenSize, GCSpawner& spawner, const sf::Font& font, unsigned int characterSize) :
    mSpawner(spawner),
    mScore(to_string(spawner.getScore()), font, characterSize),
    mLives(to_string(spawner.getNumLives()), font, characterSize),
    mScreenSize(screenSize) {
    setTextPosition();
}

void RCGui::update(sf::Time dt) {
    mScore.setString(to_string(mSpawner.getScore()));
    mLives.setString(to_string(mSpawner.getNumLives()));
    setTextPosition();
}

void RCGui::onDraw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(mScore, states);
    target.draw(mLives, states);
}

void RCGui::setTextPosition() {
    mScore.setPosition(mScreenSize.x - mScore.getLocalBounds().width - 8.0f, 0.0f);
    mLives.setPosition(mScreenSize.x - mLives.getLocalBounds().width - 8.0f, 1.25f * mScore.getLocalBounds().height);
}

}
