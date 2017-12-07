#include "id_manager.h"

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

IDManager& IDManager::instance()
{
    static auto instance = new IDManager();
    return *instance;
}
