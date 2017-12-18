#include "component__bag.h"

#include "container.h"
#include "actor.h"

#include "resource_manager.h"

const std::string BagComponent::stringID = "bag";

BagComponent::BagComponent(Actor* parent) :
    ContainerInterfaceComponent(parent),
    m_dropped(false)
{}

BagComponent::BagComponent(Container& container, Actor* parent) :
    ContainerInterfaceComponent(container, parent),
    m_dropped(false)
{}

void BagComponent::load(Json& node, ResourceManager& resManager)
{
    assert(!node.at("size").is_null());
    m_container = Container{ node.at("size").get<int>() };
    //assert(!node.at("slots").is_null());
    for (auto it = node.at("slots").begin(); it != node.at("slots").end(); ++it)
    {
        auto item = resManager.get<Item>(it.value().get<std::string>());
        m_container.addToSlot(*item, std::stoi(it.key()));
    }
}

Json BagComponent::save() const
{
    Json node;
    node["size"] = m_container.getSize();
    auto& slots = m_container.m_busyslots;
    for (auto& pair : slots)
    {
        node["slots"][std::to_string(pair.first)] = pair.second->getRes();
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