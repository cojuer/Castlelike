#include "component__loot.h"

#include "container.h"
#include "actor.h"
#include "resource_manager.h"
#include "rng.h"

const std::string LootComponent::stringID = "loot";

LootComponent::LootComponent(Actor* parent) :
	ContainerInterfaceComponent(parent)
{}

LootComponent::LootComponent(Container& container, Actor* parent) :
	ContainerInterfaceComponent(container, parent)
{}

void LootComponent::generate(Json& node, ResourceManager& resManager)
{
    // FIXME: use specific rng
    RNG rng;
    // FIXME: how to define size?
    m_container = Container(36);
    for (auto& itemNode : node)
    {
        std::string name = itemNode["name"];
        int minItems = itemNode["min"];
        int maxItems = itemNode["max"];
        int chance = itemNode["chance"];
        int amount = minItems;
        for (auto i = minItems; i < maxItems; ++i)
        {
            if (rng.getInRange(0, 100) <= chance)
            {
                ++amount;
            }
        }
        auto item = resManager.get<Item>(name);
        if (item)
        {
            item->setAmount(amount);
            m_container.add(*item);
        }
    }
}

void LootComponent::load(Json& node, ResourceManager& resManager)
{
    m_container = Container(node.at("size").get<int>());
    auto slots = node.at("slots");
    for (auto it = slots.begin(); it != slots.end(); ++it)
    {
        auto res = it.value().get<std::string>();
        auto item = resManager.get<Item>(res);
        assert(item);
        m_container.m_busyslots[std::stoi(it.key())] = item;
    }
}

Json LootComponent::save() const
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

std::string LootComponent::getStringID() const
{
    return stringID;
}

Container& LootComponent::get()
{
	return m_container;
}

LootComponent::~LootComponent() {}
