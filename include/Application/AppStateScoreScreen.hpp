#ifndef APPSTATESCORESCREEN_HPP
#define APPSTATESCORESCREEN_HPP

#include <Application/AppState.hpp>
#include <Gui/GuiContainer.hpp>
#include <GameplaySystem/ScoreRecord.hpp>

namespace mnk {

class AppStateScoreScreen : public AppState {
public:
    AppStateScoreScreen(AppStateStack& stateStack, Resources& resources);
    AppStateScoreScreen(AppStateStack& stateStack, Resources& resources, ScoreRecord::ScoreEntry newScore);
    virtual ~AppStateScoreScreen();

    virtual void handleInputEvent(const sf::Event& event);
    virtual void handleRealTimeInput();
    virtual void update(sf::Time dt);
    virtual void render();

private:
    void initGui();

private:
    ScoreRecord mScoreRecord;
    GuiContainer mGuiContainer;
};

}

#endif // APPSTATESCORESCREEN_HPP
