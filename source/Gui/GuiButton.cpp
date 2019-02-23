#include <Gui/GuiButton.hpp>
#include <Utilities/UtilityMethods.hpp>

namespace mnk {

const bool selectable = true;

GuiButton::GuiButton(const sf::Texture& normalTexture, const sf::Texture& selectedTexture, const sf::Texture& pressedTexture, const sf::Font& font) :
    GuiComponent(selectable),
    mCallback(),
    mpNormalTexture(&normalTexture),
    mpSelectedTexture(&selectedTexture),
    mpPressedTexture(&pressedTexture),
    mSprite(),
    mNormalColor(sf::Color::White),
    mSelectedColor(sf::Color::White),
    mPressedColor(sf::Color::White),
    mText("", font),
    mIsToggle(false) {
    setButtonTexture(*mpNormalTexture);
    mText.setColor(mNormalColor);
    centerOrigin(mText);
}

GuiButton::GuiButton(Callback callback,
    const sf::Texture& normalTexture, const sf::Texture& selectedTexture, const sf::Texture& pressedTexture,
    const std::string& text, const sf::Font& font, unsigned int characterSize) :
    GuiComponent(selectable),
    mCallback(callback),
    mpNormalTexture(&normalTexture),
    mpSelectedTexture(&selectedTexture),
    mpPressedTexture(&pressedTexture),
    mSprite(),
    mNormalColor(sf::Color::White),
    mSelectedColor(sf::Color::White),
    mPressedColor(sf::Color::White),
    mText(text, font, characterSize),
    mIsToggle(false) {
    setButtonTexture(*mpNormalTexture);
    mText.setColor(mNormalColor);
    centerOrigin(mText);
}

void GuiButton::setCallback(Callback callback) { mCallback = callback; }
void GuiButton::setNormalTexture(const sf::Texture& texture) { mpNormalTexture = &texture; }
void GuiButton::setSelectedTexture(const sf::Texture& texture) { mpSelectedTexture = &texture; }
void GuiButton::setPressedTexture(const sf::Texture& texture) { mpPressedTexture = &texture; }
void GuiButton::setNormalTextColor(const sf::Color& color) {
    mNormalColor = color;
    if(!isSelected() && !isActive()) {
        mText.setColor(color);
    }
}
void GuiButton::setSelectedTextColor(const sf::Color& color) {
    mSelectedColor = color;
    if(isSelected() && !isActive()) {
        mText.setColor(color);
    }
}
void GuiButton::setPressedTextColor(const sf::Color& color) {
    mPressedColor = color;
    if(!isSelected() && isActive()) {
        mText.setColor(color);
    }
}

void GuiButton::setText(const std::string& text) {
    mText.setString(text);
    centerOrigin(mText);
}

void GuiButton::setFont(const sf::Font& font) {
    mText.setFont(font);
    centerOrigin(mText);
}

void GuiButton::setCharacterSize(unsigned int value) {
    mText.setCharacterSize(value);
    centerOrigin(mText);
}

void GuiButton::setToggle(bool value) { mIsToggle = value; }

sf::FloatRect GuiButton::getLocalBounds() const {
    return mSprite.getLocalBounds();
}

void GuiButton::select() {
    GuiComponent::select();
    setButtonTexture(*mpSelectedTexture);
    mText.setColor(mSelectedColor);
}

void GuiButton::deselect() {
    GuiComponent::deselect();
    setButtonTexture(*mpNormalTexture);
    mText.setColor(mNormalColor);
}

void GuiButton::activate() {
    GuiComponent::activate();
    if(mIsToggle) {
        setButtonTexture(*mpPressedTexture);
        mText.setColor(mPressedColor);
    }
    if(mCallback) {
        mCallback();
    }
    if(!mIsToggle) {
        deactivate();
    }
}

void GuiButton::deactivate() {
    GuiComponent::deactivate();
    if(mIsToggle) {
        if(isSelected()) {
            setButtonTexture(*mpSelectedTexture);
            mText.setColor(mSelectedColor);
        } else {
            setButtonTexture(*mpNormalTexture);
            mText.setColor(mNormalColor);
        }
    }
}

void GuiButton::handleEvent(const sf::Event& event) {}

void GuiButton::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(mSprite, states);
    target.draw(mText, states);
}

void GuiButton::setButtonTexture(const sf::Texture& texture) {
    mSprite.setTexture(texture);
    centerOrigin(mSprite);
}

}
