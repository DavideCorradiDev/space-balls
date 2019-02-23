#ifndef RCANIMATEDSPRITE_HPP
#define RCANIMATEDSPRITE_HPP

#include <RenderSystem/RenderComponent.hpp>
#include <ResourceSystem/AnimatedSprite.hpp>

namespace mnk {

class RCAnimatedSprite : public RenderComponent {
public:
    RCAnimatedSprite();
    RCAnimatedSprite(const Animation& animation, sf::Time frameTime);

    AnimatedSprite& getAnimatedSprite();
    const AnimatedSprite& getAnimatedSprite() const;
    void setAnimatedSprite(const AnimatedSprite& value);

    virtual void update(sf::Time dt);

protected:
    virtual void onDraw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    AnimatedSprite mAnimatedSprite;
};

}

#endif // RCANIMATEDSPRITE_HPP
