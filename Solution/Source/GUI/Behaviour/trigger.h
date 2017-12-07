#pragma once

#include <SDL.h>

#include "widget_state.h"

namespace gui {

class Widget;

class Trigger
{
public:
    Trigger() = default;

    virtual void handle(Widget& wdg, SDL_Event& ev, WState before, WState after) = 0;

    virtual ~Trigger() = default;
};

} /* gui namespace */