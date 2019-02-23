#ifndef MSGCONTACT_HPP
#define MSGCONTACT_HPP

#include <MessageSystem/Message.hpp>
#include <PhysicsSystem/ContactInformation.hpp>

namespace mnk {

class Entity;

class MsgContact : public Message {
public:
    MsgContact(Entity& otherEntity, const ContactInformation& contactInformation) :
        otherEntity(otherEntity),
        contactInformation(contactInformation) {}
    virtual ~MsgContact() {}

public:
    Entity& otherEntity;
    const ContactInformation& contactInformation;

};

}

#endif // MSGCONTACT_HPP
