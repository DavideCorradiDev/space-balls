#include <RenderSystem/RCShape.hpp>

namespace mnk {

RCShape::RCShape() :
    RenderComponent(),
    mpShape(nullptr) {}

RCShape::RCShape(ShapePtr pShape) :
    RenderComponent(),
    mpShape(std::move(pShape)) {}

RCShape::~RCShape() {}

void RCShape::onDraw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(*mpShape, states);
}

sf::Shape* RCShape::getpShape() { return mpShape.get(); }
const sf::Shape* RCShape::getpShape() const { return mpShape.get(); }
void RCShape::setpShape(ShapePtr pShape) { mpShape = std::move(pShape); }

}
