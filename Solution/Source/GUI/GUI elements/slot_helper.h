#pragma once

#include "timer.h"

#include "helper_item.h"

class RenderSubsystem;
class ResourceManager;

namespace gui {

class Slot;

class SlotHelper
{
private:
    Timer            timer;
    Slot*            curSlot;
    ItemHelper       m_itemHelper;
public:
    SlotHelper();
    ~SlotHelper() = default;

    void             setSlot(Slot* slot);

    void             render(RenderSubsystem& rendSubsys, ResourceManager& resManager) const;
};

} /* gui namespace. */