#include "on_motion.h"

#include "subsystem__event.h"

namespace gui {

OnMotion::OnMotion(Event* event, SDL_Rect handleRect) :
    m_event(event)
{}

void OnMotion::handle(Widget& widget, SDL_Event& ev, WState before, WState after)
{
    if (before == WState::MOUSE_OUT &&
        after == WState::MOUSE_OVER)
    {
        EventSubsystem::FireEvent(*m_event);
    }
}

} /* gui namespace */