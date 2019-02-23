#ifndef STATEGAME_HPP
#define STATEGAME_HPP

#include <Application/AppState.hpp>
#include <GameWorld/GameWorld.hpp>
#include <Gui/GuiContainer.hpp>
#include <Gui/GuiLabel.hpp>
#include <Gui/GuiLivesTrack.hpp>
#include <memory>

namespace mnk {

class GCLives;

class AppStateGame : public AppState {
public:
    AppStateGame(AppStateStack& stateStack, Resources& resources);
    virtual ~AppStateGame();

    virtual void handleInputEvent(const sf::Event& event);
    virtual void handleRealTimeInput();
    virtual void update(sf::Time dt);
    virtual void render();

private:
    void initGui();
    void updateState(sf::Time dt);
    void updateGui(sf::Time dt);

private:
    GameWorld mWorld;
    GuiContainer mGuiContainer;
    std::shared_ptr<GuiLabel> mpScoreLabel;
    std::shared_ptr<GuiLivesTrack> mpLivesTrack;
};

}

#endif // STATEGAME_HPP
