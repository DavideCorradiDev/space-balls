#include <RenderSystem/RCSprite.hpp>
#include <Utilities/UtilityMethods.hpp>

namespace mnk {

RCSprite::RCSprite() :
    RenderComponent(),
    mSprite() {
    centerOrigin(mSprite);
}

RCSprite::RCSprite(const sf::Texture& texture) :
    RenderComponent(),
    mSprite(texture) {
    centerOrigin(mSprite);
}

RCSprite::RCSprite(const sf::Texture& texture, const sf::IntRect& rectangle) :
    RenderComponent(),
    mSprite(texture, rectangle) {
    centerOrigin(mSprite);
}

sf::Sprite& RCSprite::getSprite() { return mSprite; }
const sf::Sprite& RCSprite::getSprite() const { return mSprite; }
void RCSprite::setSprite(const sf::Sprite& value) {
    mSprite = value;
    centerOrigin(mSprite);
}

void RCSprite::onDraw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(mSprite, states);
}


}
