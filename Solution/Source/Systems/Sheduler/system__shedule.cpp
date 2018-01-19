#include "system__shedule.h"
#include "subsystem__event.h"

SheduleSystem::SheduleSystem() = default;

bool SheduleSystem::init()
{
    auto registered = EventSubsystem::AddHandler(*this);
    return registered;
}

bool SheduleSystem::isSheduleEmpty() const
{
    return m_eventQueue.empty();
}

void SheduleSystem::refresh()
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

void SheduleSystem::onEvent(SheduleEvent& event)
{
    m_eventQueue.push(event.m_event);
}