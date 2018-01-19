#include "component.h"

#include "actor.h"

ActorComponent::ActorComponent(Actor* parent) :
    m_parent(parent)
{}

void ActorComponent::generate(Json& node, ResourceSystem& resSystem)
{
    load(node, resSystem);
}

void ActorComponent::postGenerate(ResourceSystem& resSystem)
{
    postLoad(resSystem);
}

void ActorComponent::postLoad(ResourceSystem& resSystem)
{}

void ActorComponent::setParent(Actor& parent)
{
    m_parent = &parent;
}

Actor* ActorComponent::getParent() const
{
    return m_parent;
}

ActorComponent::~ActorComponent() {}