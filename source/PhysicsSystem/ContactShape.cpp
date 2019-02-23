#include <PhysicsSystem/ContactShape.hpp>
#include <PhysicsSystem/CSAxisAlignedRectangle.hpp>
#include <PhysicsSystem/CSCircle.hpp>
#include <Utilities/UtilityMethods.hpp>
#include <functional>
#include <map>
#include <typeindex>
#include <memory>
#include <cassert>

namespace mnk {

// Implementation of contact checking function using double dispatch.
namespace {

typedef std::function<ContactInformation(const ContactShape&, const ContactShape&)> ContactFunction;
typedef std::map<std::pair<std::type_index, std::type_index>, ContactFunction> ContactFunctionMap;

template <typename type1, typename type2>
void addContactFunction(ContactFunctionMap& contactFunctionMap, std::function<ContactInformation(const type1&, const type2&)> contactFunction);
std::unique_ptr<ContactFunctionMap> initializeContactFunctionMap() ;

ContactInformation checkAxisAlignedRectangleAndAxisAlignedRectangle(const CSAxisAlignedRectangle& AAR1, const CSAxisAlignedRectangle& AAR2);
ContactInformation checkCircleCircle(const CSCircle& circle1, const CSCircle& circle2);
ContactInformation checkAxisAlignedRectangleCircle(const CSAxisAlignedRectangle& AAR, const CSCircle& circle);
ContactInformation invertPenetrationVector(ContactInformation information);
ContactInformation checkCircleAxisAlignedRectangle(const CSCircle& circle, const CSAxisAlignedRectangle& AAR);

template <typename type1, typename type2>
void addContactFunction(ContactFunctionMap& contactFunctionMap, std::function<ContactInformation(const type1&, const type2&)> contactFunction) {
    contactFunctionMap.insert(std::make_pair(std::make_pair(std::type_index(typeid(type1)), std::type_index(typeid(type2))), [=](const ContactShape& shape1, const ContactShape& shape2) {
        ContactInformation ci = contactFunction(static_cast<const type1&>(shape1), static_cast<const type2&>(shape2));
        return ci;
    }));
}

std::unique_ptr<ContactFunctionMap> initializeContactFunctionMap() {
    std::unique_ptr<ContactFunctionMap> pContactFunctionMap (new ContactFunctionMap());
    addContactFunction<CSAxisAlignedRectangle, CSAxisAlignedRectangle>(*pContactFunctionMap, checkAxisAlignedRectangleAndAxisAlignedRectangle);
    addContactFunction<CSCircle, CSCircle>(*pContactFunctionMap, checkCircleCircle);
    addContactFunction<CSAxisAlignedRectangle, CSCircle>(*pContactFunctionMap, checkAxisAlignedRectangleCircle);
    addContactFunction<CSCircle, CSAxisAlignedRectangle>(*pContactFunctionMap, checkCircleAxisAlignedRectangle);
    return pContactFunctionMap;
}

ContactInformation checkAxisAlignedRectangleAndAxisAlignedRectangle(const CSAxisAlignedRectangle& AAR1, const CSAxisAlignedRectangle& AAR2) {
    if(AAR1.getLeft() >= AAR2.getRight()) {
        return ContactInformation(false);
    }
    if(AAR1.getRight() <= AAR2.getLeft()) {
        return ContactInformation(false);
    }
    if(AAR1.getUp() >= AAR2.getDown()) {
        return ContactInformation(false);
    }
    if(AAR1.getDown() <= AAR2.getUp()) {
        return ContactInformation(false);
    }
    sf::Vector2f distance = AAR2.getPosition() - AAR1.getPosition();
    float horizontalPenetration = (AAR1.getHalfWidth() + AAR2.getHalfWidth()) - fabs(distance.x);
    float verticalPenetration = (AAR1.getHalfHeight() + AAR2.getHalfHeight()) - fabs(distance.y);
    if(horizontalPenetration <= verticalPenetration) {
        sf::Vector2f normal;
        if(distance.x > 0) normal.x = 1;
        if(distance.x < 0) normal.x = -1;
        return ContactInformation(true, normal, horizontalPenetration);
    }
    else {
        sf::Vector2f normal;
        if(distance.y > 0) normal.y = 1;
        if(distance.y < 0) normal.y = -1;
        return ContactInformation(true, normal, verticalPenetration);
    }
}

ContactInformation checkCircleCircle(const CSCircle& circle1, const CSCircle& circle2) {
    sf::Vector2f distance = circle2.getPosition() - circle1.getPosition();
    float penetration = (circle1.getRadius() + circle2.getRadius()) - norm(distance);
    if(penetration > 0) {
        // In the special case in which the center of the circles coincide, set an arbitrary contact normal.
        if(distance == sf::Vector2f(0.0f, 0.0f)) distance = sf::Vector2f(1.0f, 0.0f);
        return ContactInformation(true, normalize(distance), penetration);
    } else {
        return ContactInformation(false);
    }
}

ContactInformation checkAxisAlignedRectangleCircle(const CSAxisAlignedRectangle& AAR, const CSCircle& circle) {
    // Placeholder. Need to implement this in the future...
    assert(false);
    return ContactInformation(false);
}

// Dual methods.
ContactInformation invertPenetrationVector(ContactInformation information) { return ContactInformation(information.contactHappened(), -information.getContactNormal(), information.getPenetration()); }
ContactInformation checkCircleAxisAlignedRectangle(const CSCircle& circle, const CSAxisAlignedRectangle& AAR) { return invertPenetrationVector(checkAxisAlignedRectangleCircle(AAR, circle)); }

}

ContactShape::~ContactShape() {}

ContactInformation checkContact(const ContactShape& shape1, const ContactShape& shape2) {
    static std::unique_ptr<ContactFunctionMap> pContactFunctionMap(initializeContactFunctionMap());
    auto found = pContactFunctionMap->find(std::make_pair(std::type_index(typeid(shape1)), std::type_index(typeid(shape2))));
    assert(found != pContactFunctionMap->end() && "checkContact - Contact detection function non found.");
    return found->second(shape1, shape2);
}

}
