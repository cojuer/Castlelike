#include "component__collision.h"
#include "actor.h"

const std::string CollisionComponent::stringID = "collision";

CollisionComponent::CollisionComponent(Actor* parent) :
    ActorComponent(parent),
    m_collisive(false)
{}

void CollisionComponent::load(Json& node, ResourceSystem& resSystem)
{
	m_collisive = node;
}

Json CollisionComponent::save() const
{
    return { { getStringID(), m_collisive } };
}

std::string CollisionComponent::getStringID() const
{
    return stringID;
}

const bool& CollisionComponent::get() const
{
	return m_collisive;
}

void CollisionComponent::set(bool collisive)
{
	m_collisive = collisive;
}
