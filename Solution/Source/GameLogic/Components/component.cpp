#include "component.h"

#include "actor.h"

ActorComponent::ActorComponent(Actor* parent) :
    m_parent(parent)
{}

Json ActorComponent::toJSON() const
{
    return Json();
}

void ActorComponent::setParent(Actor& parent)
{
    m_parent = &parent;
}

Actor* ActorComponent::getParent() const
{
    return m_parent;
}

ActorComponent::~ActorComponent() {}