#pragma once

#include "widget__slot.h"

class Item;

namespace gui {

class ItemSlot : public Slot
{
public:
    ItemSlot(const std::string& name, Widget* parent, SDL_Rect geometry);

    void             setItem(Item& item);
    void             setPressed(bool state);
    void             eraseItem();

    Item*            getItem() const;

    bool             isEmpty() const override;

    bool             handle(SDL_Event& event, Vec2i coordStart) override;
    void             render(RenderSubsystem& rendSubsystem, ResourceManager& resManager, Vec2i coordStart) const override;

protected:
    Item*            m_item;
};

} /* gui namespace. */