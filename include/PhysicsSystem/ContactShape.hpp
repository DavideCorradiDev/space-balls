#ifndef CONTACTSHAPE_HPP
#define CONTACTSHAPE_HPP

#include <PhysicsSystem/ContactInformation.hpp>
#include <SFML/Graphics/Transformable.hpp>

namespace mnk {

class ContactShape : public sf::Transformable {
public:
    virtual ~ContactShape() = 0;

    virtual float getUp() const = 0;
    virtual float getDown() const = 0;
    virtual float getLeft() const = 0;
    virtual float getRight() const = 0;
};

ContactInformation checkContact(const ContactShape& shape1, const ContactShape& shape2);

}

#endif // CONTACTSHAPE_HPP
