#ifndef MESSAGEHANDLER_HPP
#define MESSAGEHANDLER_HPP

#include <functional>
#include <map>
#include <typeindex>


namespace mnk {

class Message;

class MessageHandler {
public:
    typedef std::function<void(const Message&)> MessageCallback;
    typedef std::map<std::type_index, MessageCallback> CallbackMap;

public:
    virtual ~MessageHandler() = 0;

    template <typename MessageClass>
    void addCallback(std::function<void(const MessageClass&)> callback);
    template <typename MessageClass>
    void removeCallback();
    virtual void handleMessage(const Message& message);

private:
    CallbackMap mCallbacks;
};

template <typename MessageClass>
void MessageHandler::addCallback(std::function<void(const MessageClass&)> callback) {
    mCallbacks.insert(std::make_pair(std::type_index(typeid(MessageClass)), [=](const Message& message) {
        return callback(static_cast<const MessageClass&>(message));
    }));
}

template <typename MessageClass>
    void MessageHandler::removeCallback() {
    mCallbacks.erase(std::type_index(typeid(MessageClass)));
}

}

#endif // MESSAGEHANDLER_HPP
