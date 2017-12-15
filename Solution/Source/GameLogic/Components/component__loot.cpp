#include "component__loot.h"

#include "container.h"
#include "actor.h"
#include "resource_manager.h"

RNG LootComponent::m_lootRng;
const std::string LootComponent::stringID = "loot";

LootComponent::LootComponent(Actor* parent) :
	ContainerInterfaceComponent(parent)
{}

LootComponent::LootComponent(Container& container, Actor* parent) :
	ContainerInterfaceComponent(container, parent)
{}

void LootComponent::fromJSON(Json& node, ResourceManager& resManager)
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
    // TODO: move to some loot generator
    //for (auto& itemNode : node)
    //{
    //    std::string name = itemNode["name"];
    //    int minItems = itemNode["min"];
    //    int maxItems = itemNode["max"];
    //    int chance = itemNode["chance"];
    //    // TODO: add multiple items in stacks if possible
    //    for (auto i = 0; i < maxItems; ++i)
    //    {
    //        if (i < minItems || m_lootRng.getInRange(0, 100) <= chance)
    //        {
    //            auto item = resManager.get<Item>(name);
    //            assert(item);
    //            if (item)
    //            {
    //                m_container.add(*item);
    //            }
    //        }
    //    }
    //}
}

Json LootComponent::toJSON() const
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
