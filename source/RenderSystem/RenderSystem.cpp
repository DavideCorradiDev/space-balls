#include <RenderSystem/RenderSystem.hpp>

namespace mnk {

RenderSystem::RenderSystem(sf::RenderTarget& renderTarget) :
    GameSystem<RenderComponent>(),
    mpRenderTarget(renderTarget) {}

RenderSystem::~RenderSystem() {}

void RenderSystem::onUpdateObject(sf::Time dt, RenderComponent& object) {
    object.update(dt);
}

void RenderSystem::render() {
    for(const GameSystem<RenderComponent>::ObjectPtr& pObj : getObjectsList()) {
        mpRenderTarget.draw(*pObj);
    }
}

}
