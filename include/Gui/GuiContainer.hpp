#ifndef GUICONTAINER_HPP
#define GUICONTAINER_HPP

#include <Gui/GuiComponent.hpp>
#include <vector>

namespace mnk {

class GuiContainer : public GuiComponent {
public:
    std::shared_ptr<GuiComponent> Ptr;

public:
    GuiContainer();

    void addComponent(GuiComponent::Ptr component);

    virtual void handleEvent(const sf::Event& event);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    bool hasSelection() const;
    void select(std::size_t index);
    void selectNext();
    void selectPrevious();

private:
    std::vector<GuiComponent::Ptr> mChildren;
    int mSelectedChild;
};

}

#endif // GUICONTAINER_HPP
