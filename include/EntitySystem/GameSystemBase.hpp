#ifndef GAMESYSTEMBASE_HPP
#define GAMESYSTEMBASE_HPP

#include <MessageSystem/MessageHandler.hpp>

// This Base class is defined to allow having pointers to a GameSystem, which is a template class.

namespace mnk{

class GameSystemBase : public MessageHandler {
public:
    virtual ~GameSystemBase() = 0;
};

}

#endif // GAMESYSTEMBASE_HPP
