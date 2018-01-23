#include "GUI/Behaviour/behaviour.h"

#include "trigger.h"
#include "widget.h"

namespace gui {
    
Bhvr::Bhvr(Widget& parent, TrigVec&& trigs) :
    m_parent(parent),
    m_trigs(trigs)
{}

Bhvr::~Bhvr()
{
    for (auto trig : m_trigs)
    {
        delete(trig);
    }
    // TODO: use C++17 auto& [] when possible
    for (auto pair : m_keyTrigs)
    {
        delete(pair.second);
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

void Bhvr::changeState(SDL_Event& ev, Vec2i coordStart)
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
        if (ev.type == SDL_EventType::SDL_MOUSEBUTTONDOWN)
        {
            m_parent.setState(WState::PRESSED);
        }
        else if (ev.type == SDL_EventType::SDL_MOUSEMOTION &&
            !m_parent.isPointOn({ x, y }, coordStart))
        {
            m_parent.setState(WState::MOUSE_OUT);
        }
        break;
    case WState::PRESSED:
        if (ev.type == SDL_EventType::SDL_MOUSEBUTTONUP)
        {
            m_parent.setState(WState::MOUSE_OVER);
        }
        else if (ev.type == SDL_EventType::SDL_MOUSEMOTION &&
            !m_parent.isPointOn({ x, y }, coordStart))
        {
            m_parent.setState(WState::PRESSED_MOUSE_OUT);
        }
        break;
    case WState::PRESSED_MOUSE_OUT:
        if (ev.type == SDL_EventType::SDL_MOUSEBUTTONUP)
        {
            m_parent.setState(WState::MOUSE_OUT);
        }
        else if (ev.type == SDL_EventType::SDL_MOUSEMOTION &&
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