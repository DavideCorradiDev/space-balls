#include <Application/Application.hpp>
#include <Application/AppConstants.hpp>
#include <Application/AppStateMainMenu.hpp>
#include <Application/AppStateUnfocused.hpp>
#include <Utilities/UtilityMethods.hpp>

namespace mnk {

Application::Application() :
    mUpdateTime(sf::seconds(AppConstants::UPDATE_TIME)),
    mRenderTime(sf::seconds(AppConstants::RENDER_TIME)),
    #ifndef NDEBUG
    mFps(),
    #endif
    mStateStack(mResources),
    mRenderWindow(sf::VideoMode(AppConstants::DISPLAY_WIDTH, AppConstants::DISPLAY_HEIGHT
        , AppConstants::DISPLAY_BITSPERPIXEL)
        , AppConstants::APPLICATION_NAME, AppConstants::WINDOW_STYLE),
    mAnimationHolder(),
    mFontHolder(),
    mMusicPlayer(),
    mSoundBufferHolder(),
    mTextureHolder(),
    mResources(mRenderWindow, mAnimationHolder, mFontHolder, mMusicPlayer, mSoundBufferHolder, mTextureHolder) {

    mRenderWindow.setKeyRepeatEnabled(false);

    mFontHolder.load(FontId::MenuFont, "./resources/font/Sansation.ttf");
    mFontHolder.load(FontId::MonospaceFont, "./resources/font/PTM55F.ttf");

    mMusicPlayer.load(MusicId::MainMenu, "./resources/music/menu_theme.ogg");
    mMusicPlayer.load(MusicId::Game, "./resources/music/game_theme.ogg");

    mSoundBufferHolder.load(SoundBufferId::Explosion, "./resources/audio/explosion.wav");
    mSoundBufferHolder.load(SoundBufferId::Shoot, "./resources/audio/shoot.wav");
    mSoundBufferHolder.load(SoundBufferId::Engine, "./resources/audio/engine.wav");
    mSoundBufferHolder.load(SoundBufferId::NewLife, "./resources/audio/newlife.wav");
    mSoundBufferHolder.load(SoundBufferId::Ufo, "./resources/audio/ufo.wav");

    mTextureHolder.load(TextureId::Ship, "./resources/bitmap/ship_animation.png");
    mTextureHolder.load(TextureId::Bullet, "./resources/bitmap/bullet.png");
    mTextureHolder.load(TextureId::SpaceBall, "./resources/bitmap/ball_big.png");
    mTextureHolder.load(TextureId::Explosion, "./resources/bitmap/explosion.png");
    mTextureHolder.load(TextureId::ButtonNormal, "./resources/bitmap/button_normal.png");
    mTextureHolder.load(TextureId::ButtonSelected, "./resources/bitmap/button_selected.png");
    mTextureHolder.load(TextureId::ButtonPressed, "./resources/bitmap/button_pressed.png");
    mTextureHolder.load(TextureId::SpaceBackground, "./resources/bitmap/background.png");
    mTextureHolder.load(TextureId::Ufo, "./resources/bitmap/ufo.png");

    std::unique_ptr<Animation> pAnimationShip(new Animation(mTextureHolder.get(TextureId::Ship)));
    for(unsigned int i = 0; i < 4; i++) {
        pAnimationShip->addFrame(sf::IntRect(i*48, 0, 48, 48));
    }
    mAnimationHolder.add(AnimationId::Ship, std::move(pAnimationShip));

    std::unique_ptr<Animation> pAnimationExplosion(new Animation(mTextureHolder.get(TextureId::Explosion)));
    for(unsigned int i = 0; i < 10; i++) {
        pAnimationExplosion->addFrame(sf::IntRect(i*48, 0, 48, 48));
    }
    mAnimationHolder.add(AnimationId::Explosion, std::move(pAnimationExplosion));

    #ifndef NDEBUG
    mFps.setFont(mFontHolder.get(AppConstants::FPS_FONT));
    mFps.setCharacterSize(AppConstants::FPS_SIZE);
    mFps.setString(to_string(0.0f));
    #endif

    mStateStack.push(AppState::Ptr(new AppStateMainMenu(mStateStack, mResources)));
}

void Application::run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time timeSinceLastRender = sf::Time::Zero;
    while(mRenderWindow.isOpen()) {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;
        timeSinceLastRender += dt;
        while(timeSinceLastUpdate > mUpdateTime) {
            timeSinceLastUpdate -= mUpdateTime;
                handleInput();
                update(mUpdateTime);
        }
        if(timeSinceLastRender > mRenderTime) {
            render();
            #ifndef NDEBUG
            mFps.setString(to_string(1.0f / timeSinceLastRender.asSeconds()));
            #endif
            while(timeSinceLastRender > mRenderTime) {
                timeSinceLastRender -= mRenderTime;
            }
        }
    }
}

void Application::handleInput() {
    sf::Event event;
    while(mRenderWindow.pollEvent(event)) {
        switch(event.type) {
        case sf::Event::Closed:
            mRenderWindow.close();
            break;
        case sf::Event::LostFocus:
            mStateStack.push(AppState::Ptr(new AppStateUnfocused(mStateStack, mResources)));
            break;
        case sf::Event::GainedFocus:
            mStateStack.pop();
            break;
        default:
            break;
        }
        mStateStack.handleInputEvent(event);
    }
    mStateStack.handleRealTimeInput();
}

void Application::update(sf::Time dt) {
    mStateStack.update(dt);
    // This check has to be done after the update, so that if there are pending changes on the state stack they have the chance to be performed.
    if(mStateStack.empty()) {
        mRenderWindow.close();
    }
}

void Application::render() {
    mRenderWindow.clear();
    mStateStack.render();
    #ifndef NDEBUG
    mRenderWindow.draw(mFps);
    #endif
    mRenderWindow.display();
}

}
