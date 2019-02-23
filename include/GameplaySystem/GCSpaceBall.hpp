#ifndef GCSPACEBALL_HPP
#define GCSPACEBALL_HPP

#include <GameplaySystem/GameplayComponent.hpp>
#include <EntitySystem/EDSpaceBall.hpp>

namespace mnk {

class EntityFactory;

class GCSpaceBall : public GameplayComponent {
public:
    GCSpaceBall(EntityFactory& entityFactory, EDSpaceBall::Size size);
    virtual ~GCSpaceBall();

private:
    void destroy();

private:
    EntityFactory& mEntityFactory;
    EDSpaceBall::Size mSize;
};

}

#endif // GCSPACEBALL_HPP
