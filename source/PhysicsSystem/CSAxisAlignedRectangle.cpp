#include <PhysicsSystem/CSAxisAlignedRectangle.hpp>
#include <cassert>

namespace mnk {

CSAxisAlignedRectangle::CSAxisAlignedRectangle(float halfWidth, float halfHeight) :
    mHalfWidth(halfWidth),
    mHalfHeight(halfHeight) {
    assert(halfWidth >= 0);
    assert(halfHeight >= 0);
}

CSAxisAlignedRectangle::~CSAxisAlignedRectangle() {}

float CSAxisAlignedRectangle::getHalfWidth() const { return mHalfWidth; }
float CSAxisAlignedRectangle::getHalfHeight() const { return mHalfWidth; }
void CSAxisAlignedRectangle::setHalfWidth(float value) {
    assert(value >= 0);
    mHalfWidth = value;
}
void CSAxisAlignedRectangle::setHalfHeight(float value) {
    assert(value >= 0);
    mHalfHeight = value;
}

float CSAxisAlignedRectangle::getUp() const { return getPosition().y - mHalfHeight; }
float CSAxisAlignedRectangle::getDown() const { return getPosition().y + mHalfHeight; }
float CSAxisAlignedRectangle::getLeft() const { return getPosition().x - mHalfWidth; }
float CSAxisAlignedRectangle::getRight() const { return getPosition().x + mHalfWidth; }

}
