#include "component__transform.h"
#include "actor.h"

const std::string TransformComponent::stringID = "transform";

TransformComponent::TransformComponent(Actor* parent) :
    ActorComponent(parent),
    m_transform({ { 0, 0 }, 0, 0 })
{}

Json TransformComponent::save() const
{
    Json node;
    node["x"] = m_transform.m_shift.x;
    node["y"] = m_transform.m_shift.y;
    return { { getStringID(), node } };
}

void TransformComponent::load(Json& node, ResourceSystem& resSystem)
{
    m_transform.m_shift.x = node["x"];
    m_transform.m_shift.y = node["y"];
}

std::string TransformComponent::getStringID() const
{
    return stringID;
}

const Transform& TransformComponent::get() const
{
    return m_transform;
}

void TransformComponent::set(Transform transform)
{
    m_transform = transform;
}
