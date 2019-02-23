#ifndef EDUFO_HPP
#define EDUFO_HPP

#include <EntitySystem/EntityData.hpp>

namespace mnk  {

class EDUfo : public EntityData {
public:
    enum class Type {
        Dumb,
        Smart,
    };

public:
    EDUfo(Type type) :
        type(type) {}
    virtual ~EDUfo() {}

public:
    Type type;

};

}

#endif // EDUFO_HPP
