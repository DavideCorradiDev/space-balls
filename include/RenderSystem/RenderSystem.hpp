#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include <EntitySystem/GameSystem.hpp>
#include <RenderSystem/RenderComponent.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace mnk {

class RenderSystem : public GameSystem<RenderComponent> {
public:
    RenderSystem(sf::RenderTarget& renderTarget);
    virtual ~RenderSystem();

    void render();

private:
    virtual void onUpdateObject(sf::Time dt, RenderComponent& object);

private:
    sf::RenderTarget& mpRenderTarget;
};

}

#endif // RENDERSYSTEM_HPP
