#pragma once

#include "event.h"
#include "menu_state.h"

class MenuEvent : public Event
{
public:
    MenuState newState;

    explicit MenuEvent(MenuState newState, Object* sender = nullptr) : Event(sender)
    {
        this->newState = newState;
    }

    virtual ~MenuEvent() {};
};