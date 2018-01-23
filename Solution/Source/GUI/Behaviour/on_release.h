#pragma once

#include "trigger.h"

class Event;

namespace gui {

class OnRelease : public Trigger
{
public:
    explicit OnRelease(Event* event = nullptr, SDL_Rect handleRect = { 0, 0, 0, 0 });
    ~OnRelease();

    void handle(Widget& widget, SDL_Event& ev, WState before, WState after) override;

protected:
    Event* m_event;
};

} /* gui namespace */