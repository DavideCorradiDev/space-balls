#ifndef RCSHAPE_HPP
#define RCSHAPE_HPP

#include <RenderSystem/RenderComponent.hpp>
#include <memory>

namespace mnk {

class RCShape : public RenderComponent {
public:
    typedef std::unique_ptr<sf::Shape> ShapePtr;

public:
    RCShape();
    RCShape(ShapePtr pShape);
    virtual ~RCShape();

    sf::Shape* getpShape();
    const sf::Shape* getpShape() const;
    void setpShape(ShapePtr pShape);

protected:
    virtual void onDraw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    ShapePtr mpShape;
};

}

#endif // RCSHAPE_HPP
