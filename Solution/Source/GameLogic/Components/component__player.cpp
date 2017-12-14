#include "component__player.h"
#include "actor.h"

const std::string PlayerComponent::stringID = "player";

PlayerComponent::PlayerComponent(Actor* parent) :
    ActorComponent(parent),
    m_possessed(false)
{}

void PlayerComponent::fromJSON(Json& node, ResourceManager& resManager)
{
    // non-loadable
}

std::string PlayerComponent::getStringID() const
{
    return stringID;
}

bool PlayerComponent::possess()
{
    if (!m_possessed)
    {
        m_possessed = true;
        return true;
    }
    return false;
}

bool PlayerComponent::isPossessed() const
{
    return m_possessed;
}

PlayerComponent::~PlayerComponent()
{}