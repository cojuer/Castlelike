#include "component__bag.h"

#include "container.h"
#include "actor.h"

const std::string BagComponent::stringID = "bag";

BagComponent::BagComponent(Actor* parent) :
    ContainerInterfaceComponent(parent),
    m_dropped(false)
{}

BagComponent::BagComponent(Container& container, Actor* parent) :
    ContainerInterfaceComponent(container, parent),
    m_dropped(false)
{}

void BagComponent::fromJSON(Json& node, ResourceManager& resManager)
{
	// non-loadable
}

Json BagComponent::toJSON() const
{
    Json node;
    auto& slots = m_container.m_busyslots;
    for (auto& pair : slots)
    {
        node[pair.first] = pair.second->getRes();
    }
    return { { getStringID() , node } };
}

std::string BagComponent::getStringID() const
{
    return stringID;
}

Container& BagComponent::get()
{
	return m_container;
}

bool BagComponent::isDropped() const
{
    return m_dropped;
}

BagComponent::~BagComponent()
{}