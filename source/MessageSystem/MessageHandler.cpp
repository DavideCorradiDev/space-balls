#include <MessageSystem/MessageHandler.hpp>
#include <MessageSystem/Message.hpp>

namespace mnk {

MessageHandler::~MessageHandler() {}

void MessageHandler::handleMessage(const Message& message) {
    auto found = mCallbacks.find(std::type_index(typeid(message)));
    if(found != mCallbacks.end()) {
        found->second(message);
    }
}

}
