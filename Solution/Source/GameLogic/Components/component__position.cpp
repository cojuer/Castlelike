#include "component__position.h"
#include "actor.h"

const std::string PositionComponent::stringID = "position";

PositionComponent::PositionComponent(Actor* parent) :
	ActorComponent(parent)
{}

Json PositionComponent::toJSON() const
{
    Json node;
    node["x"] = m_position.x;
    node["y"] = m_position.y;
    return { { getStringID(), node } };
}

void PositionComponent::fromJSON(Json& node, ResourceManager& resManager)
{
	m_position.x = node["x"];
	m_position.y = node["y"];
}

std::string PositionComponent::getStringID() const
{
    return stringID;
}

const Coord& PositionComponent::get() const
{
	return m_position;
}

PositionComponent::~PositionComponent() {}

void PositionComponent::set(Coord position)
{
	m_position = position;
}
