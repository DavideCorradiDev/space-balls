#include <Gui/GuiComponent.hpp>

namespace mnk {

GuiComponent::GuiComponent() :
    mSelectable(false),
    mSelected(false),
    mActive(false) {}

GuiComponent::GuiComponent(bool selectable) :
    mSelectable(selectable),
    mSelected(false),
    mActive(false) {}

GuiComponent::~GuiComponent() {}

bool GuiComponent::isSelectable() const { return mSelectable; }

bool GuiComponent::isSelected() const { return mSelected; }
void GuiComponent::select() { mSelected = true; }
void GuiComponent::deselect() { mSelected = false; }

bool GuiComponent::isActive() const { return mActive; }
void GuiComponent::activate() { mActive = true; }
void GuiComponent::deactivate() { mActive = false; }

}
