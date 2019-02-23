#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <Application/AppStateStack.hpp>
#include <ResourceSystem/Resources.hpp>
#include <Utilities/NonCopyable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

namespace mnk {

class Application : public NonCopyable {
public:
    Application();

    void run();

private:
    void handleInput();
    void update(sf::Time dt);
    void render();

private:
    const sf::Time mUpdateTime;
    const sf::Time mRenderTime;

    #ifndef NDEBUG
    sf::Text mFps;
    #endif

    AppStateStack mStateStack;

    sf::RenderWindow mRenderWindow;
    AnimationHolder mAnimationHolder;
    FontHolder mFontHolder;
    MusicPlayer mMusicPlayer;
    SoundBufferHolder mSoundBufferHolder;
    TextureHolder mTextureHolder;
    Resources mResources;
};

}

#endif // APPLICATION_HPP
