#pragma once

#include <memory>

#include "trigger.h"

class Event;

namespace gui {

class OnRelease : public Trigger
{
public:
    explicit OnRelease(Event* event = nullptr, SDL_Rect handleRect = { 0, 0, 0, 0 });

    void handle(Widget& widget, SDL_Event& ev, WState before, WState after) override;

protected:
    std::unique_ptr<Event> m_event;
};

} /* gui namespace */