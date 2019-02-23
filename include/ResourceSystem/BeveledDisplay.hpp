#ifndef BEVELEDDISPLAY_HPP
#define BEVELEDDISPLAY_HPP

#include <Utilities/NonCopyable.hpp>
#include <SFML/Graphics.hpp>
#include <string>

namespace mnk {

class BeveledDisplay : public NonCopyable {
public:
    BeveledDisplay(unsigned int width, unsigned int height, unsigned int bitsPerPixel, const sf::String& title, sf::Uint32 style = sf::Style::Default, const sf::ContextSettings& settings = sf::ContextSettings());

    const sf::RenderTarget& getRenderTarget() const;
    const sf::RenderWindow& getRenderWindow() const;

    bool isOpen() const;
    void close();
    bool pollEvent(sf::Event& event);
    bool waitEvent(sf::Event& event);

    void clear(const sf::Color& color = sf::Color(0, 0, 0, 255));
    sf::Vector2u getSize() const;
    const sf::View& getView() const;
    void setView(const sf::View& view);
    void draw(const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default);

    void display();

private:
    sf::RenderTexture mRenderTexture;
    sf::Sprite mRenderTextureSprite;
    sf::Texture mBeveledPixelTexture;
    sf::Sprite mBeveledPixelSprite;
    sf::RenderWindow mRenderWindow;
    sf::RenderStates mRenderStates;
};

}

#endif // BEVELEDDISPLAY_HPP
