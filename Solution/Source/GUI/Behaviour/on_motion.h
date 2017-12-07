#pragma once

#include "trigger.h"
#include "widget_state.h"

class Event;

namespace gui {

class OnMotion : public Trigger
{
public:
    explicit OnMotion(Event* event = nullptr, SDL_Rect handleRect = { 0, 0, 0, 0 });

    void handle(Widget& widget, SDL_Event& ev, WState before, WState after) override;

protected:
    Event*           m_event;
};

} /* gui namespace. */