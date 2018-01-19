#include "slot_helper.h"

#include <iostream>
#include <string>
#include <vector>

#include "item.h"
#include "slot__item.h"
#include "modifiers.h"
#include "system__resource.h"
#include "subsystem_render.h"
#include "text_renderer.h"
#include "font_data.h"

namespace gui {

SlotHelper::SlotHelper() :
    curSlot(nullptr)
{}

void SlotHelper::setSlot(Slot* slot)
{
    timer.stop();
    curSlot = slot;
    if (slot && !slot->isEmpty())
    {
        if (curSlot->getSlotType() == SlotType::ITEM)
        {
            auto bagSlot = dynamic_cast<ItemSlot*>(curSlot);
            auto& item = *(bagSlot->getItem());
            m_itemHelper.setItem(item);
        }
        timer.start();
    }
}

void SlotHelper::render(RenderSubsystem& rendSubsys, ResourceSystem& resSystem) const
{
    int x, y;
    SDL_GetMouseState(&x, &y);

    Vec2i pos(x, y - 65);

    std::vector<std::string> strings;
    if (curSlot && !curSlot->isEmpty())
    {
        if (curSlot->getSlotType() == SlotType::ITEM)
        {
            m_itemHelper.render(rendSubsys, resSystem);
        }
    }
}

} /* gui namespace. */