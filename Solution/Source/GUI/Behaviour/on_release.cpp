#include "on_release.h"

#include "subsystem__event.h"

namespace gui {

OnRelease::OnRelease(Event* event, SDL_Rect handleRect) :
    m_event(event)
{}

OnRelease::~OnRelease()
{
    delete(m_event);
}

void OnRelease::handle(Widget& widget, SDL_Event& ev, WState before, WState after)
{
    if (!m_event) return;

    if (before == WState::PRESSED &&
        after == WState::MOUSE_OVER)
    {
        EventSubsystem::FireEvent(*m_event);
    }
}

}