#include <Gui/GuiScore.hpp>
#include <Utilities/UtilityMethods.hpp>

namespace mnk {

const float scoreOffset = 128.0f;
const float width = 160.0f;

GuiScore::GuiScore(const ScoreRecord& record, const sf::Font& font, const unsigned int size) :
    GuiComponent(false),
    mpScoreRecord(&record),
    mpFont(&font),
    mCharacterSize(size) {
    setOrigin(width * 0.5f, 0.0f);
}

GuiScore::~GuiScore() {}

void GuiScore::handleEvent(const sf::Event& event) {}

const ScoreRecord* GuiScore::getScoreRecord() const { return mpScoreRecord; }

void GuiScore::setScoreRecord(const ScoreRecord& value) { mpScoreRecord = &value; }

sf::FloatRect GuiScore::getLocalBounds() const {
    return sf::FloatRect(0.0f, 0.0f, width, mpScoreRecord->getMaxScoreEntries() * 2.0f * mCharacterSize);
}

void GuiScore::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    sf::Text name("", *mpFont, mCharacterSize);
    sf::Text score("", *mpFont, mCharacterSize);
    score.move(scoreOffset, 0.0f);
    for(std::size_t i = 0; i < mpScoreRecord->getNumberOfEntries(); ++i) {
        name.setString((*mpScoreRecord)[i].name);
        score.setString(to_string((*mpScoreRecord)[i].score));
        centerOriginX(score);
        target.draw(name, states);
        target.draw(score, states);
        states.transform.translate(0.0f, 2.0f * mCharacterSize);
    }
    name.setString("________");
    score.setString("0");
    centerOriginX(score);
    for(std::size_t i = mpScoreRecord->getNumberOfEntries(); i < mpScoreRecord->getMaxScoreEntries(); ++i) {
        target.draw(name, states);
        target.draw(score, states);
        states.transform.translate(0.0f, 2.0f * mCharacterSize);
    }
}

}
