#include "slot_helper.h"

#include <string>
#include <vector>

#include "subsystem__render.h"
#include "system__resource.h"

#include "item.h"
#include "slot__item.h"
#include "slot__action.h"

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
        else if (curSlot->getSlotType() == SlotType::SKILL)
        {
            auto actionSlot = dynamic_cast<ActSlot*>(curSlot);
            m_actionHelper.setAction(actionSlot->getAction());
        }
        timer.start();
    }
}

void SlotHelper::render(RenderSubsystem& rendSubsys, ResourceSystem& resSystem) const
{
    int x, y;
    SDL_GetMouseState(&x, &y);

    std::vector<std::string> strings;
    if (curSlot && !curSlot->isEmpty())
    {
        if (curSlot->getSlotType() == SlotType::ITEM)
        {
            m_itemHelper.render(rendSubsys, resSystem, { 0, 0 });
        }
        else if (curSlot->getSlotType() == SlotType::SKILL)
        {
            m_actionHelper.render(rendSubsys, resSystem, { 0, 0 });
        }
    }
}

} /* gui namespace. */