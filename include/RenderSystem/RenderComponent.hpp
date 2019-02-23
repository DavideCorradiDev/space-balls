#ifndef RENDERCOMPONENT_HPP
#define RENDERCOMPONENT_HPP

#include <EntitySystem/Component.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

namespace mnk {

class RenderComponent : public Component, public sf::Drawable {
public:
    RenderComponent();
    virtual ~RenderComponent() = 0;

    virtual void update(sf::Time dt);

    bool isVisible() const;
    void setVisible(bool value);

protected:
    virtual void onDraw(sf::RenderTarget& target, sf::RenderStates states) const;   // draw sets the right transform. On draw can be overloaded with the actual drawing routine.

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    bool mVisible;
};

}

#endif // RENDERCOMPONENT_HPP
