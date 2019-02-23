#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <MessageSystem/MessageHandler.hpp>
#include <Utilities/NonCopyable.hpp>
#include <SFML/System/Time.hpp>

namespace mnk {

class GameSystemBase;

class GameObject : public MessageHandler, public NonCopyable {
public:
    enum class Status {
        Inactive,
        SetForActivation,
        Active,
        Deleted,
    };

public:
    GameObject();
    virtual ~GameObject() = 0;

    bool isSetForActivation() const;
    bool isActive() const;
    void setActive();
    virtual bool isDeleted() const; // This is virtual to allow specific game objects to partially control their deletion time (e.g. don't be deleted until the sound it is playing is over).
    void setDeleted();

    GameSystemBase* getpSystem() const;
    void setpSystem(GameSystemBase* pSystem);
    void sendMessageToSystem(const Message& message) const;

private:
    virtual void onActivation();

private:
    Status mStatus;
    GameSystemBase* mpSystem;
};

}

#endif // GAMEOBJECT_HPP
