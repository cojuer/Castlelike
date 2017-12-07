#include "widget__slot.h"

namespace gui {

Slot::Slot(const std::string& name, Widget* parent, SDL_Rect geometry, SlotType slotType) :
    Widget(name, parent, geometry, true),
    m_slotType(slotType),
    m_pressed(false)
{}

bool Slot::isPressed() const
{
    return m_pressed;
}

bool Slot::isEmpty() const
{
    return true;
}

SlotType Slot::getSlotType() const
{
    return m_slotType;
}

} /* gui namespace. */