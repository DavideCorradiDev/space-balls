#ifndef CONTACTINFORMATION_HPP
#define CONTACTINFORMATION_HPP

#include <SFML/System/Vector2.hpp>

namespace mnk {

class ContactInformation {
public:
    ContactInformation(bool contactHappened, const sf::Vector2f& contactNormal = sf::Vector2f(0.0, 0.0), float penetration = 0.0);

    bool contactHappened() const;
    const sf::Vector2f& getContactNormal() const;
    float getPenetration() const;

private:
    bool mContactHappened;
    sf::Vector2f mContactNormal;
    float mPenetration;
};

}

#endif // CONTACTINFORMATION_HPP
