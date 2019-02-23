#ifndef GUICOMPONENT_HPP
#define GUICOMPONENT_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <memory>

namespace mnk {

class GuiComponent :
    public sf::Drawable,
    public sf::Transformable,
    private sf::NonCopyable {
public:
    typedef std::shared_ptr<GuiComponent> Ptr;

public:
    GuiComponent();
    GuiComponent(bool selectable);
    virtual ~GuiComponent();

    bool isSelectable() const;

    bool isSelected() const;
    virtual void select();
    virtual void deselect();

    bool isActive() const;
    virtual void activate();
    virtual void deactivate();

    virtual void handleEvent(const sf::Event& event) = 0;

private:
    bool mSelectable;
    bool mSelected;
    bool mActive;
};

}

#endif // GUICOMPONENT_HPP
