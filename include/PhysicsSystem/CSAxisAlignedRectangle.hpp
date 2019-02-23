#ifndef CSAXISALIGNEDRECTANGLE_HPP
#define CSAXISALIGNEDRECTANGLE_HPP

#include <PhysicsSystem/ContactShape.hpp>

namespace mnk {

class CSAxisAlignedRectangle : public ContactShape {
public:
    CSAxisAlignedRectangle(float halfWidth, float halfHeight);
    virtual ~CSAxisAlignedRectangle();

    float getHalfWidth() const;
    float getHalfHeight() const;
    void setHalfWidth(float value);
    void setHalfHeight(float value);

    virtual float getUp() const;
    virtual float getDown() const;
    virtual float getLeft() const;
    virtual float getRight() const;

private:
    float mHalfWidth;
    float mHalfHeight;
};



}

#endif // CSAXISALIGNEDRECTANGLE_hPP
