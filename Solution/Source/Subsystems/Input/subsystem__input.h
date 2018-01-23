#pragma once

#include <list>

#include <SDL.h>

class InputSubsystem
{
public:
    void update();

    const std::list<SDL_Event>& getEvents() const;
private:
    std::list<SDL_Event> m_events;
};
