#include "on_motion.h"

#include "event_bus.h"

namespace gui {

OnMotion::OnMotion(Event* event, SDL_Rect handleRect) :
    m_event(event)
{}

void OnMotion::handle(Widget& widget, SDL_Event& ev, WState before, WState after)
{
    if (before == WState::MOUSE_OUT &&
        after == WState::MOUSE_OVER)
    {
        EventBus::FireEvent(*m_event);
    }
}

} /* gui namespace */