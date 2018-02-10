#pragma once

#include <SDL.h>

#include "widget_state.h"

namespace gui {

class Widget;

class Trigger
{
public:
    Trigger() = default;

    Trigger(const Trigger&) = delete;
    Trigger(Trigger&&) = default;
    Trigger& operator=(const Trigger&) = delete;
    Trigger& operator=(Trigger&&) = default;

    virtual ~Trigger() = default;

    virtual void handle(Widget& wdg, SDL_Event& ev, WState before, WState after) = 0;
};

} /* gui namespace */