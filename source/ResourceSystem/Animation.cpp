#include <ResourceSystem/Animation.hpp>
#include <cassert>

namespace mnk {

Animation::Animation() :
    mpTexture(nullptr),
    mFrames() {}

Animation::Animation(const sf::Texture& texture) :
    mpTexture(&texture),
    mFrames() {}

const sf::Texture* Animation::getpTexture() const { return mpTexture; }
void Animation::setTexture(const sf::Texture& texture) { mpTexture = &texture; }

const sf::IntRect& Animation::getFrame(unsigned int index) const {
    assert(index >= 0 && index < mFrames.size());
    return mFrames[index];
}

void Animation::addFrame(const sf::IntRect& frame) {
    mFrames.push_back(frame);
}

std::size_t Animation::getNumberOfFrames() const { return mFrames.size(); }

}
