#include "system__stats.h"

#include <iostream>

#include "id_manager.h"
#include "system_manager.h"

#include "event_bus.h"

#include "component__bag.h"
#include "component__attr.h"
#include "component__mdfr.h"

bool StatsSystem::init(SystemManager& sysManager)
{
    m_sysManager = &sysManager;

    EventBus::AddHandler(*this);

    return true;
}

bool StatsSystem::reg(Actor& actor)
{
    auto attrComponent = actor.getComponent<AttrComponent>();
    auto mdfrComponent = actor.getComponent<MdfrComponent>();
    if (attrComponent || mdfrComponent)
    {
        m_registered.insert(std::make_pair(actor.getID(), &actor));
        return true;
    }
    return false;
}

void StatsSystem::unreg(ActorID id)
{
    m_registered.erase(id);
}

void StatsSystem::update()
{
    while (!m_updated.empty())
    {
        auto actor = m_updated.front();
        auto mdfrComponent = actor->getComponent<MdfrComponent>();
        if (mdfrComponent)
        {
            mdfrComponent->refresh();
        }
        m_updated.pop();
    }
}

void StatsSystem::onEvent(ActorEvent& event)
{
    std::cout << "on actor event" << std::endl;
    auto it = m_registered.find(event.m_actorID);
    if (it != m_registered.end())
    {
        m_updated.push(it->second);
    }
}
