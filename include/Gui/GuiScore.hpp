#ifndef GUISCORE_HPP
#define GUISCORE_HPP

#include <Gui/GuiComponent.hpp>
#include <GameplaySystem/ScoreRecord.hpp>

namespace mnk {

class GuiScore : public GuiComponent {
public:
    GuiScore(const ScoreRecord& record, const sf::Font& font, const unsigned int size = 30);
    virtual ~GuiScore();

    virtual void handleEvent(const sf::Event& event);

    const ScoreRecord* getScoreRecord() const;
    void setScoreRecord(const ScoreRecord& value);

    sf::FloatRect getLocalBounds() const;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    const ScoreRecord* mpScoreRecord;
    const sf::Font* mpFont;
    unsigned int mCharacterSize;
};

}

#endif // GUISCORE_HPP
