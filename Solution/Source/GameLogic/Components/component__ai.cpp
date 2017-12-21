#include "component__ai.h"

#include "AI/behaviour.h"
#include "actor.h"

const std::string AIComponent::stringID = "ai";

AIComponent::AIComponent(Actor* parent) :
    ActorComponent(parent), 
    m_bhvr(nullptr), 
    m_possessed(false)
{}

AIComponent::AIComponent(Behaviour& bhvr, Actor* parent) :
    ActorComponent(parent),
    m_bhvr(&bhvr), 
    m_possessed(false)
{}

void AIComponent::load(Json& node, ResourceManager& resManager)
{
    // nothing to load
}

Json AIComponent::save() const
{
    return { { getStringID(), "" } };
}

std::string AIComponent::getStringID() const
{
    return stringID;
}

Behaviour* AIComponent::get() const
{
    return m_bhvr;
}

bool AIComponent::possess()
{
    if (!m_possessed)
    {
        m_possessed = true;
        return true;
    }
    return false;
}

bool AIComponent::isPossessed() const
{
    return m_possessed;
}

AIComponent::~AIComponent()
{
    delete(m_bhvr);
}
