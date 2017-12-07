#include "component__experience.h"

const std::string ExperienceComponent::stringID = "experience";

ExperienceComponent::ExperienceComponent(Actor* parent) :
    ExperienceInterfaceComponent(parent)
{
    m_xpToLvlUp = ExperienceComponent::countXpToLvlUp(m_level);
}

ExperienceComponent::ExperienceComponent(int level, int xp, Actor* parent) :
    ExperienceInterfaceComponent(level, xp, parent)
{
    m_xpToLvlUp = ExperienceComponent::countXpToLvlUp(m_level);
}

std::string ExperienceComponent::getStringID() const
{
    return stringID;
}

int ExperienceComponent::countXpToLvlUp(int level) const
{
    // TODO: some formula needed
    return (level + 1) * 100;
}

ExperienceComponent::~ExperienceComponent() {}
