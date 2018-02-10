#pragma once

#include "timer.h"

#include "helper_item.h"

class RenderSubsystem;
class ResourceSystem;

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

    void             setSlot(Slot* slot);

    void             render(RenderSubsystem& rendSubsys, ResourceSystem& resSystem) const;
};

} /* gui namespace. */