#include <RenderSystem/RenderComponent.hpp>
#include <MessageSystem/MsgSetVisible.hpp>

namespace mnk {

RenderComponent::RenderComponent() :
    Component(),
    mVisible(true) {
    addCallback<MsgSetVisible>([this](const MsgSetVisible& message) {
        mVisible = message.visible;
    });
}

RenderComponent::~RenderComponent() {}

void RenderComponent::update(sf::Time dt) {}

bool RenderComponent::isVisible() const { return mVisible; }
void RenderComponent::setVisible(bool value) { mVisible = value; }

void RenderComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if(mVisible) {
        states.transform *= getTransform();
        onDraw(target, states);
    }
}

void RenderComponent::onDraw(sf::RenderTarget& target, sf::RenderStates states) const {}

}
