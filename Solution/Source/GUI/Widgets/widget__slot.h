#pragma once

#include "widget.h"

namespace gui {

constexpr int defaultSlotWidth  = 32;
constexpr int defaultSlotHeight = 32;

enum class SlotType
{
    NONE = 0,
    ITEM = 1,
    SKILL = 2
};

class Slot : public Widget
{
public:
    Slot(const std::string& name, Widget* parent, SDL_Rect geometry, SlotType slotType);

    SlotType getSlotType() const;

    bool isPressed() const;
    virtual bool isEmpty() const;

protected:
    SlotType m_slotType;
    bool     m_pressed;// FIXME: delete
};

} /* gui namespace. */
