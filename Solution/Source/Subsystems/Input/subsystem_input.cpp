#include "subsystem_input.h"

void InputSubsystem::update()
{
    m_events.erase(m_events.begin(), m_events.end());
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        m_events.push_back(event);
    }
}

const std::list<SDL_Event>& InputSubsystem::getEvents() const
{
    return m_events;
}
