#include <RenderSystem/RCAnimatedSprite.hpp>
#include <Utilities/UtilityMethods.hpp>

namespace mnk {

RCAnimatedSprite::RCAnimatedSprite() :
    RenderComponent(),
    mAnimatedSprite() {
    centerOrigin(mAnimatedSprite);
}

RCAnimatedSprite::RCAnimatedSprite(const Animation& animation, sf::Time frameTime) :
    RenderComponent(),
    mAnimatedSprite(animation, frameTime) {
    centerOrigin(mAnimatedSprite);
}

AnimatedSprite& RCAnimatedSprite::getAnimatedSprite() { return mAnimatedSprite; }
const AnimatedSprite& RCAnimatedSprite::getAnimatedSprite() const { return mAnimatedSprite; }
void RCAnimatedSprite::setAnimatedSprite(const AnimatedSprite& value) {
    mAnimatedSprite = value;
    centerOrigin(mAnimatedSprite);
}

void RCAnimatedSprite::update(sf::Time dt) {
    mAnimatedSprite.update(dt);
    // Need too call it again in case different frames have different sizes...
    centerOrigin(mAnimatedSprite);
}

void RCAnimatedSprite::onDraw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(mAnimatedSprite, states);
}

}
