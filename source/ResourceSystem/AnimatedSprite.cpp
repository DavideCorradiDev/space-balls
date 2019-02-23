#include <ResourceSystem/AnimatedSprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <cassert>
#include <algorithm>

namespace mnk {

AnimatedSprite::AnimatedSprite() :
    mpAnimation(nullptr),
    mFrameTime(sf::seconds(0.0f)),
    mCurrentTime(sf::seconds(0.0f)),
    mCurrentFrame(0),
    mPaused(false),
    mLooping(false) {}

AnimatedSprite::AnimatedSprite(const Animation& animation, sf::Time frameTime) :
    mpAnimation(&animation),
    mFrameTime(frameTime),
    mCurrentTime(sf::seconds(0.0f)),
    mCurrentFrame(0),
    mPaused(false),
    mLooping(false) {}

void AnimatedSprite::update(sf::Time dt) {
    if(!isPaused()) {
        mCurrentTime += dt;
        while(mCurrentTime >= mFrameTime) {
            mCurrentTime -= mFrameTime;
            increaseCurrentFrame();
        }
    }
}

const Animation* AnimatedSprite::getAnimation() const { return mpAnimation; }

void AnimatedSprite::setAnimation(const Animation& animation) {
    mpAnimation = &animation;
    setCurrentFrame(0);
}

sf::Time AnimatedSprite::getFrameTime() const { return mFrameTime; }

void AnimatedSprite::setFrameTime(sf::Time value) {
    mFrameTime = value;
    mCurrentTime = sf::seconds(0.0f);
}

void AnimatedSprite::setDuration(sf::Time value) {
    assert(mpAnimation);
    mFrameTime = sf::seconds(value.asSeconds() / static_cast<float>(mpAnimation->getNumberOfFrames()));
    mCurrentTime = sf::seconds(0.0f);
}

std::size_t AnimatedSprite::getCurrentFrame() const { return mCurrentFrame; }

bool AnimatedSprite::hasEnded() const {
    assert(mpAnimation);
    return mCurrentFrame == mpAnimation->getNumberOfFrames();
}

void AnimatedSprite::setCurrentFrame(std::size_t value) {
    assert(mpAnimation);
    assert(value >= 0 && value <= mpAnimation->getNumberOfFrames());
    value = std::max(std::size_t(0), std::min(value, mpAnimation->getNumberOfFrames()));
    mCurrentFrame = value;
    mCurrentTime = sf::seconds(0.0f);
}

void AnimatedSprite::increaseCurrentFrame() {
    assert(mpAnimation);
    mCurrentFrame++;
    if(mCurrentFrame >= mpAnimation->getNumberOfFrames()) {
        if(isLooping()) {
            mCurrentFrame = 0;
        } else {
            mCurrentFrame = mpAnimation->getNumberOfFrames();
        }
    }
    assert(mCurrentFrame >= 0 && mCurrentFrame <= mpAnimation->getNumberOfFrames());
}

void AnimatedSprite::restart() {
    mCurrentFrame = 0;
}

bool AnimatedSprite::isPaused() const { return mPaused; }
void AnimatedSprite::play() { mPaused = false; }
void AnimatedSprite::pause() { mPaused = true; }

bool AnimatedSprite::isLooping() const { return mLooping; }
void AnimatedSprite::setLooping(bool value) { mLooping = value; }

void AnimatedSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    assert(mpAnimation);
    assert(mpAnimation->getNumberOfFrames() > 0);
    // mCurrentFrame can assume a value equal to the number of frames if the animation has ended. In such a situation, have to reduce the index by one.
//    std::size_t index = mCurrentFrame;
//    if(index >= mpAnimation->getNumberOfFrames()) --index;
    states.transform *= getTransform();
    target.draw(sf::Sprite(*(mpAnimation->getpTexture()), mpAnimation->getFrame(getFrameIndex())), states);
}

std::size_t AnimatedSprite::getFrameIndex() const {
    if(mCurrentFrame < mpAnimation->getNumberOfFrames()) return mCurrentFrame;
    else return mCurrentFrame - 1;
}

sf::FloatRect AnimatedSprite::getLocalBounds() const {
    assert(mpAnimation);
    assert(mpAnimation->getNumberOfFrames() > 0);
    return sf::FloatRect(0.0f, 0.0f,
                         static_cast<float>(mpAnimation->getFrame(getFrameIndex()).width),
                         static_cast<float>(mpAnimation->getFrame(getFrameIndex()).height));
}
sf::FloatRect AnimatedSprite::getGlobalBounds() const {
    assert(mpAnimation);
    assert(mpAnimation->getNumberOfFrames() > 0);
    return getTransform().transformRect(getLocalBounds());
}

}
