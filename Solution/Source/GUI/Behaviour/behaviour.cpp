#include "GUI/Behaviour/behaviour.h"

#include "trigger.h"
#include "widget.h"

namespace gui {

Bhvr::Bhvr(Widget& parent, std::vector<Trigger*>&& triggers) : 
    m_parent(parent)
{
    for (auto trigger : triggers)
    {
        m_trigs.emplace_back(trigger);
    }
}

WState Bhvr::behave(SDL_Event& ev, Vec2i coordStart)
{
    WState before = m_parent.getState();
    changeState(ev, coordStart);
    WState after = m_parent.getState();

    for (auto& trigger : m_trigs)
    {
        trigger->handle(m_parent, ev, before, after);
    }

    m_parent.setState(after);
    return after;
}

void Bhvr::changeState(SDL_Event& event, Vec2i coordStart)
{
    auto& state = m_parent.getState();

    if (state == WState::INACTIVE ||
        state == WState::HIDDEN)
    {
        return;
    }

    int x, y;
    SDL_GetMouseState(&x, &y);

    if (state == WState::MOUSE_OUT &&
        m_parent.isPointOn({ x, y }, coordStart))
    {
        m_parent.setState(WState::MOUSE_OVER);
    }

    switch (state)
    {
    case WState::MOUSE_OVER:
        if (event.type == SDL_EventType::SDL_MOUSEBUTTONDOWN)
        {
            m_parent.setState(WState::PRESSED);
        }
        else if (event.type == SDL_EventType::SDL_MOUSEMOTION &&
            !m_parent.isPointOn({ x, y }, coordStart))
        {
            m_parent.setState(WState::MOUSE_OUT);
        }
        break;
    case WState::PRESSED:
        if (event.type == SDL_EventType::SDL_MOUSEBUTTONUP)
        {
            m_parent.setState(WState::MOUSE_OVER);
        }
        else if (event.type == SDL_EventType::SDL_MOUSEMOTION &&
            !m_parent.isPointOn({ x, y }, coordStart))
        {
            m_parent.setState(WState::PRESSED_MOUSE_OUT);
        }
        break;
    case WState::PRESSED_MOUSE_OUT:
        if (event.type == SDL_EventType::SDL_MOUSEBUTTONUP)
        {
            m_parent.setState(WState::MOUSE_OUT);
        }
        else if (event.type == SDL_EventType::SDL_MOUSEMOTION &&
            m_parent.isPointOn({ x, y }, coordStart))
        {
            m_parent.setState(WState::PRESSED);
        }
        break;
    default:
        break;
    }
}

} /* gui namespace. */