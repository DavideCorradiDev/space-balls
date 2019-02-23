#include <Gui/GuiContainer.hpp>

namespace mnk {

GuiContainer::GuiContainer() :
    GuiComponent(false),
    mChildren(),
    mSelectedChild(-1) {}

void GuiContainer::addComponent(GuiComponent::Ptr component) {
    mChildren.push_back(component);
    if(!hasSelection() && component->isSelectable()) {
        select(mChildren.size()-1);
    }
}

void GuiContainer::handleEvent(const sf::Event& event) {
    if(hasSelection() && mChildren[mSelectedChild]->isActive()) {
        mChildren[mSelectedChild]->handleEvent(event);
    } else {
        switch(event.type) {
        case sf::Event::KeyReleased:
            switch(event.key.code) {
            case sf::Keyboard::Up:
                selectPrevious();
                break;
            case sf::Keyboard::Down:
                selectNext();
                break;
            case sf::Keyboard::Return:
                if(hasSelection()) {
                    mChildren[mSelectedChild]->activate();
                }
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }
}

void GuiContainer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    for(const GuiComponent::Ptr& child : mChildren) {
        target.draw(*child, states);
    }
}

bool GuiContainer::hasSelection() const {
    return mSelectedChild >= 0;
}

void GuiContainer::select(std::size_t index) {
    if(mChildren[index]->isSelectable()) {
        if(hasSelection()) {
            mChildren[mSelectedChild]->deselect();
        }
        mChildren[index]->select();
        mSelectedChild = index;
    }
}

void GuiContainer::selectNext() {
    if(!hasSelection()) {
        return;
    }

    int next = mSelectedChild;
    do {
        next = (next + 1) % mChildren.size();
    } while(!mChildren[next]->isSelectable());

    select(next);
}

void GuiContainer::selectPrevious() {
    if(!hasSelection()) {
        return;
    }

    int prev = mSelectedChild;
    do {
        prev = (prev + mChildren.size() - 1) % mChildren.size();
    } while(!mChildren[prev]->isSelectable());

    select(prev);
}

}
