#ifndef CSCIRCLE_HPP
#define CSCIRCLE_HPP

#include <PhysicsSystem/ContactShape.hpp>

namespace mnk {

class CSCircle : public ContactShape {
public:
    CSCircle(float radius);
    virtual ~CSCircle();

    float getRadius() const;
    void setRadius(float value);

    virtual float getUp() const;
    virtual float getDown() const;
    virtual float getLeft() const;
    virtual float getRight() const;

private:
    float mRadius;
};



}

#endif // CSCIRCLE_HPP
