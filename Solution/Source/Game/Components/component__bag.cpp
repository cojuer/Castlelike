#include "component__bag.h"

#include "container.h"
#include "actor.h"

#include "system__resource.h"

const std::string BagComponent::stringID = "bag";

BagComponent::BagComponent(Actor* parent) :
    ContainerInterfaceComponent(parent),
    m_dropped(false)
{}

BagComponent::BagComponent(Container&& container, Actor* parent) :
    ContainerInterfaceComponent(std::move(container), parent),
    m_dropped(false)
{}

void BagComponent::load(Json& node, ResourceSystem& resSystem)
{
    assert(!node.at("size").is_null());
    m_container = Container{ node.at("size").get<uint32_t>() };
    //assert(!node.at("slots").is_null());
    for (auto it = node.at("slots").begin(); it != node.at("slots").end(); ++it)
    {
        auto item = resSystem.get<Item>(it.value().get<std::string>());
        m_container.addToSlot(*item, std::stoi(it.key()));
    }
}

Json BagComponent::save() const
{
    Json node;
    node["size"] = m_container.getSize();
    auto& slots = m_container.m_busyslots;
    for (auto&[index, item] : slots)
    {
        node["slots"][std::to_string(index)] = item->getRes();
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