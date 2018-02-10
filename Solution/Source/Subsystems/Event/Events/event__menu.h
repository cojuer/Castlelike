#pragma once

#include "event.h"
#include "menu_state.h"

class MenuEvent final : public Event
{
public:
    MenuState m_state;

    explicit MenuEvent(MenuState state, Object* sender = nullptr) : Event(sender)
    {
        m_state = state;
    }
};