#include "component__position.h"
#include "actor.h"

const std::string PositionComponent::stringID = "position";

PositionComponent::PositionComponent(Actor* parent) :
	ActorComponent(parent)
{}

Json PositionComponent::save() const
{
    Json node;
    node["x"] = m_position.x;
    node["y"] = m_position.y;
    return { { getStringID(), node } };
}

void PositionComponent::load(Json& node, ResourceSystem& resSystem)
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

void PositionComponent::set(Coord position)
{
	m_position = position;
}
