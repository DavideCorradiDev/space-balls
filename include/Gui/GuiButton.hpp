#ifndef GUIBUTTON_HPP
#define GUIBUTTON_HPP

#include <Gui/GuiComponent.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <memory>
#include <functional>
#include <string>

namespace mnk {

class GuiButton : public GuiComponent {
public:
    typedef std::shared_ptr<GuiButton> Ptr;
    typedef std::function<void()> Callback;

public:
    GuiButton(const sf::Texture& normalTexture, const sf::Texture& selectedTexture, const sf::Texture& pressedTexture, const sf::Font& font);
    GuiButton(Callback callback,
        const sf::Texture& normalTexture, const sf::Texture& selectedTexture, const sf::Texture& pressedTexture,
        const std::string& text, const sf::Font& font, unsigned int characterSize);

    void setCallback(Callback callback);
    void setNormalTexture(const sf::Texture& texture);
    void setSelectedTexture(const sf::Texture& texture);
    void setPressedTexture(const sf::Texture& texture);
    void setNormalTextColor(const sf::Color& color);
    void setSelectedTextColor(const sf::Color& color);
    void setPressedTextColor(const sf::Color& color);
    void setText(const std::string& string);
    void setFont(const sf::Font& font);
    void setCharacterSize(unsigned int value);
    void setToggle(bool value);

    sf::FloatRect getLocalBounds() const;

    virtual void select();
    virtual void deselect();
    virtual void activate();
    virtual void deactivate();
    virtual void handleEvent(const sf::Event& event);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void setButtonTexture(const sf::Texture& texture);

private:
    Callback mCallback;
    const sf::Texture* mpNormalTexture;
    const sf::Texture* mpSelectedTexture;
    const sf::Texture* mpPressedTexture;
    sf::Sprite mSprite;
    sf::Color mNormalColor;
    sf::Color mSelectedColor;
    sf::Color mPressedColor;
    sf::Text mText;
    bool mIsToggle;
};

}

#endif // GUIBUTTON_HPP
