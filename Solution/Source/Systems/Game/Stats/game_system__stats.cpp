#include "game_system__stats.h"

#include <iostream>

#include "id_manager.h"
#include "game_system_manager.h"

#include "subsystem__event.h"

#include "component__bag.h"
#include "component__attr.h"
#include "component__mdfr.h"

bool StatsGSystem::init(GameSystemManager& sysManager)
{
    m_sysManager = &sysManager;

    EventSubsystem::AddHandler(*this);

    return true;
}

bool StatsGSystem::reg(Actor& actor)
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

void StatsGSystem::unreg(ActorID id)
{
    m_registered.erase(id);
}

void StatsGSystem::update()
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

void StatsGSystem::onEvent(ActorEvent& event)
{
    auto it = m_registered.find(event.m_actorID);
    if (it != m_registered.end())
    {
        m_updated.push(it->second);
    }
}
