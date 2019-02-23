#ifndef RCGUI_HPP
#define RCGUI_HPP

#include <RenderSystem/RenderComponent.hpp>
#include <GameplaySystem/GCSpawner.hpp>

namespace mnk {

class RCGui : public RenderComponent {
public:
    RCGui(const sf::Vector2f& screenSize, GCSpawner& spawner, const sf::Font& font, unsigned int characterSize = 30);

    virtual void update(sf::Time dt);

protected:
    virtual void onDraw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    void setTextPosition();

private:
    GCSpawner& mSpawner;
    sf::Text mScore;
    sf::Text mLives;
    sf::Vector2f mScreenSize;
};

}

#endif // RCGUI_HPP
