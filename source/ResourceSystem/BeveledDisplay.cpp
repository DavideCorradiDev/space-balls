#include <ResourceSystem/BeveledDisplay.hpp>
#include <Application/AppConstants.hpp>
#include <cassert>

namespace mnk {

BeveledDisplay::BeveledDisplay(unsigned int width, unsigned int height, unsigned int bitsPerPixel, const sf::String& title, sf::Uint32 style, const sf::ContextSettings& settings) :
    mRenderTexture(),
    mRenderTextureSprite(),
    mBeveledPixelTexture(),
    mBeveledPixelSprite(),
    mRenderWindow(),
    mRenderStates() {

    mRenderTexture.create(width, height);
    mRenderTextureSprite.setTexture(mRenderTexture.getTexture());

    bool loaded = mBeveledPixelTexture.loadFromFile(AppConstants::BEVELED_PIXEL_PATH);
    assert(loaded && mBeveledPixelTexture.getSize().x == mBeveledPixelTexture.getSize().y);
    unsigned int pixelSize = mBeveledPixelTexture.getSize().x;
    mBeveledPixelTexture.setRepeated(true);
    mBeveledPixelSprite.setTexture(mBeveledPixelTexture);
    mBeveledPixelSprite.setTextureRect(sf::IntRect(0, 0, pixelSize*width, pixelSize*height));

    mRenderWindow.create(sf::VideoMode(width*pixelSize, height*pixelSize, bitsPerPixel), title, style, settings);

    mRenderStates.transform.scale(pixelSize, pixelSize);
}

const sf::RenderTarget& BeveledDisplay::getRenderTarget() const { return mRenderTexture; }
const sf::RenderWindow& BeveledDisplay::getRenderWindow() const { return mRenderWindow; };

bool BeveledDisplay::isOpen() const { return mRenderWindow.isOpen(); }
void BeveledDisplay::close() { mRenderWindow.close(); }
bool BeveledDisplay::pollEvent(sf::Event& event) { return mRenderWindow.pollEvent(event); }
bool BeveledDisplay::waitEvent(sf::Event& event) { return mRenderWindow.waitEvent(event); }

void BeveledDisplay::clear(const sf::Color& color) { mRenderTexture.clear(color); }
sf::Vector2u BeveledDisplay::getSize() const { return mRenderTexture.getSize(); }
const sf::View& BeveledDisplay::getView() const { return mRenderTexture.getView(); }
void BeveledDisplay::setView(const sf::View& view) { mRenderTexture.setView(view); }
void BeveledDisplay::draw(const sf::Drawable& drawable, const sf::RenderStates& states) { mRenderTexture.draw(drawable, states); }

void BeveledDisplay::display() {
    mRenderTexture.display();
    mRenderWindow.draw(mRenderTextureSprite, mRenderStates);
    mRenderWindow.draw(mBeveledPixelSprite);
    mRenderWindow.display();
}

}
