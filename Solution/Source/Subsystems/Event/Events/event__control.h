#pragma once

#include "event.h"
#include "actor.h"

enum class CONTROL {
    ENABLE,
    DISABLE
};

class ControlEvent : public Event
{
public:
    ControlEvent(CONTROL new_state, Object* sender = nullptr) :
        Event(sender),
        m_state(new_state)
    {}

    CONTROL m_state;
};
