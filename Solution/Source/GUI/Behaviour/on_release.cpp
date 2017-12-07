#include "on_release.h"

#include "event_bus.h"

namespace gui {

OnRelease::OnRelease(Event* event, SDL_Rect handleRect) :
    m_event(event)
{}

void OnRelease::handle(Widget& widget, SDL_Event& ev, WState before, WState after)
{
    if (!m_event) return;

    if (before == WState::PRESSED &&
        after == WState::MOUSE_OVER)
    {
        EventBus::FireEvent(*m_event);
    }
}

}