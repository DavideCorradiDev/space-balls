#ifndef GAMESYSTEM_HPP
#define GAMESYSTEM_HPP

#include <EntitySystem/GameSystemBase.hpp>
#include <EntitySystem/GameObject.hpp>
#include <SFML/System/Time.hpp>
#include <memory>
#include <list>
#include <cassert>

// This class is a template because systems work with specific types of objects, with specific interfaces, and need to know such interfaces.

namespace mnk {

template <typename ObjType>
class GameSystem : public GameSystemBase {
public:
    typedef std::unique_ptr<ObjType> ObjectPtr;
    typedef std::list<ObjectPtr> ObjectsList;

public:
    virtual ~GameSystem() = 0;

    void update(sf::Time dt);

    virtual void handleMessage(const Message& message);
    const ObjectsList& getObjectsList() const;
    void addObject(ObjectPtr pObject);   // By value because GameSystem takes ownership of the pointer.
    void removeObject(ObjType& object);
    void sendMessageToObjects(const Message& message) const;

private:
    virtual void onAddObject(ObjType& object);
    virtual void onUpdateObject(sf::Time dt, ObjType& object);
    virtual void onUpdateEnd(sf::Time dt);

private:
    ObjectsList mpObjects;
};

//template <typename ObjType>
//void addObjectToSystem(std::unique_ptr<ObjType> pObject, GameSystem<ObjType>& system);

}

#include "../../source/EntitySystem/GameSystem.inl"

#endif // GAMESYSTEM_HPP
