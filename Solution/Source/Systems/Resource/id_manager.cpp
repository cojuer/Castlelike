#include "id_manager.h"

const std::string IDManager::stringID = "system__id";

IDManager::IDManager() :
    m_current(0)
{}

ActorID IDManager::getActorID()
{
    if (!m_freed.empty())
    {
        auto result = m_freed.front();
        m_freed.pop_front();
        return result;
    }
    else
    {
        m_current += 1;
        return m_current;
    }
}

void IDManager::free(ActorID id)
{
    m_freed.push_back(id);
}

void IDManager::load(const Json& node, ResourceSystem& resSystem)
{
    m_current = node.at("current");
    for (auto it = node.at("free").begin(); it != node.at("free").end(); ++it)
    {
        m_freed.push_back(*it);
    }
}

Json IDManager::save() const
{
    Json result;
    result["current"] = m_current;
    result["free"] = m_freed;
    return result;
}

IDManager& IDManager::instance()
{
    static auto instance = new IDManager();
    return *instance;
}

std::string IDManager::getStringID() const
{
    return stringID;
}
