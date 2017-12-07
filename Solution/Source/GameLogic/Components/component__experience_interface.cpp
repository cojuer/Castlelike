#include "component__experience_interface.h"

#include "actor.h"

ExperienceInterfaceComponent::ExperienceInterfaceComponent(Actor* parent) :
    ActorComponent(parent),
    m_level(0),
    m_xp(0),
    m_xpToLvlUp(0)
{}

ExperienceInterfaceComponent::ExperienceInterfaceComponent(int level, int xp, Actor* parent) :
    ActorComponent(parent),
    m_level(level),
    m_xp(xp),
    m_xpToLvlUp(0)
{}

void ExperienceInterfaceComponent::fromJSON(Json& node, ResourceManager& resManager)
{
    // non-loadable
}

void ExperienceInterfaceComponent::addXP(int xp)
{
    m_xp += xp;
}

void ExperienceInterfaceComponent::setXpToLvlUp(int xpToLvlUp)
{
    m_xpToLvlUp = xpToLvlUp;
}

const int& ExperienceInterfaceComponent::getXp() const
{
    return m_xp;
}

const int& ExperienceInterfaceComponent::getXpToLvlUp() const
{
    return m_xpToLvlUp;
}
const int& ExperienceInterfaceComponent::getLevel() const
{
    return m_level;
}

void ExperienceInterfaceComponent::updateLvl()
{
    while (m_xp >= m_xpToLvlUp)
    {
        m_xp -= m_xpToLvlUp;
        ++m_level;
        m_xpToLvlUp = countXpToLvlUp(m_level);
    }
}

ExperienceInterfaceComponent::~ExperienceInterfaceComponent() {}
