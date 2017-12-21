#include "component.h"

#include "actor.h"

ActorComponent::ActorComponent(Actor* parent) :
    m_parent(parent)
{}

void ActorComponent::generate(Json& node, ResourceManager& resManager)
{
    load(node, resManager);
}

void ActorComponent::postGenerate(ResourceManager& resManager)
{
    postLoad(resManager);
}

void ActorComponent::postLoad(ResourceManager& resManager)
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