#ifndef GCBULLET_HPP
#define GCBULLET_HPP

#include <GameplaySystem/GameplayComponent.hpp>

namespace mnk {

class EntityFactory;

class GCBullet : public GameplayComponent {
public:
    GCBullet(EntityFactory& entityFactory, float lifeTime, bool ofPlayer);
    virtual ~GCBullet();

    virtual void update(sf::Time dt);

private:
    EntityFactory& mEntityFactory;
    float mLifeTime;
    bool mOfPlayer;
};

}

#endif // GCBULLET_HPP
