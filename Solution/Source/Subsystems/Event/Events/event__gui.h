#pragma once

#include "event.h"

enum class EventId
{
    NONE = 0,
    HERO_MOVED,
    START_DIALOG,
    REFRESH_DIALOG
};

class GUIEvent : public Event
{
public:
    const EventId    id;

    GUIEvent(EventId id, Object* sender = nullptr) :
        Event(sender),
        id(id)
    {}

    virtual ~GUIEvent() {};
};
