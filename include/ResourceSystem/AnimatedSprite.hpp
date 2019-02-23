#ifndef ANIMATEDSPRITE_HPP
#define ANIMATEDSPRITE_HPP

#include <ResourceSystem/Animation.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Time.hpp>

namespace mnk {

class AnimatedSprite : public sf::Drawable, public sf::Transformable {
public:
    AnimatedSprite();
    AnimatedSprite(const Animation& animation, sf::Time frameTime);

    void update(sf::Time dt);

    const Animation* getAnimation() const;
    void setAnimation(const Animation& animation);

    sf::Time getFrameTime() const;
    void setFrameTime(sf::Time value);
    void setDuration(sf::Time value);

    std::size_t getCurrentFrame() const;
    bool hasEnded() const;
    void setCurrentFrame(std::size_t value);
    void increaseCurrentFrame();
    void restart();

    bool isPaused() const;
    void play();
    void pause();

    bool isLooping() const;
    void setLooping(bool value);

    sf::FloatRect getLocalBounds() const;
    sf::FloatRect getGlobalBounds() const;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    std::size_t getFrameIndex() const;

private:
    const Animation* mpAnimation;
    sf::Time mFrameTime;
    sf::Time mCurrentTime;
    std::size_t mCurrentFrame;
    bool mPaused;
    bool mLooping;
};

}

#endif // ANIMATEDSPRITE_HPP
