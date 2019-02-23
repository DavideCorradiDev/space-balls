#include <PhysicsSystem/ContactInformation.hpp>

namespace mnk {

ContactInformation::ContactInformation(bool contactHappened, const sf::Vector2f& contactNormal, float penetration) :
    mContactHappened(contactHappened),
    mContactNormal(contactNormal),
    mPenetration(penetration) {}

bool ContactInformation::contactHappened() const { return mContactHappened; }
const sf::Vector2f& ContactInformation::getContactNormal() const { return mContactNormal; }
float ContactInformation::getPenetration() const { return mPenetration; }


}
