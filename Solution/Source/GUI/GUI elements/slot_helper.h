#pragma once

#include "timer.h"

#include "helper_item.h"
#include "helper_action.h"

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
    ActionHelper     m_actionHelper;
public:
    SlotHelper();

    void             setSlot(Slot* slot);

    void             render(RenderSubsystem& rendSubsys, ResourceSystem& resSystem) const;
};

} /* gui namespace. */