#include "game_sheduler.h"
#include "event_bus.h"

Sheduler::Sheduler() = default;

bool Sheduler::init()
{
    auto registered = EventBus::AddHandler(*this);
    return registered;
}

bool Sheduler::isSheduleEmpty() const
{
    return m_eventQueue.empty();
}

void Sheduler::refresh()
{
    if (m_player.onCutscene())
    {
        m_player.updateCutscene();
    }
    if (!m_player.onCutscene() && !m_eventQueue.empty())
    {
        // TODO: use timer to divide long chains of actions
        while (!m_eventQueue.empty() && std::holds_alternative<ActionInterface*>(m_eventQueue.front()))
        {
            auto action = std::get<ActionInterface*>(m_eventQueue.front());
            action->act();
            m_eventQueue.pop();
        }
        if (!m_eventQueue.empty() && std::holds_alternative<Cutscene*>(m_eventQueue.front()))
        {
            auto& cutscene = *std::get<Cutscene*>(m_eventQueue.front());
            m_player.startCutscene(cutscene);
            m_eventQueue.pop();
        }
    }
}

void Sheduler::onEvent(SheduleEvent& event)
{
    std::cout << "on shedule event" << std::endl;
    m_eventQueue.push(event.m_event);
}