#include <PhysicsSystem/CSCircle.hpp>
#include <cassert>

namespace mnk {

CSCircle::CSCircle(float radius) :
    mRadius(radius) {
    assert(radius > 0);
}

CSCircle::~CSCircle() {}

float CSCircle::getRadius() const { return mRadius; }
void CSCircle::setRadius(float value) {
    assert(value > 0);
    mRadius = value;
}

float CSCircle::getUp() const { return getPosition().y - mRadius; }
float CSCircle::getDown() const { return getPosition().y + mRadius; }
float CSCircle::getLeft() const { return getPosition().x - mRadius; }
float CSCircle::getRight() const { return getPosition().x + mRadius; }

}
