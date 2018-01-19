#include "component__loot.h"

#include "container.h"
#include "actor.h"
#include "system__resource.h"
#include "rng.h"
#include "rng_holder.h"

const std::string LootComponent::stringID = "loot";

LootComponent::LootComponent(Actor* parent) :
	ContainerInterfaceComponent(parent)
{}

LootComponent::LootComponent(Container& container, Actor* parent) :
	ContainerInterfaceComponent(container, parent)
{}

void LootComponent::generate(Json& node, ResourceSystem& resSystem)
{
    auto& rngHolder = *resSystem.getRNGHolder();
    auto rng = rngHolder.getRNG(RNGType::LOOT);
    if (!rng)
    {
        rng = rngHolder.regRNG(RNGType::LOOT, RNG{ 0, 0, 100 });
        assert(rng && "RNG registration failure");
    }
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
            if (rng->get() <= chance)
            {
                ++amount;
            }
        }
        auto item = resSystem.get<Item>(name);
        if (item)
        {
            item->setAmount(amount);
            m_container.add(*item);
        }
    }
}

void LootComponent::load(Json& node, ResourceSystem& resSystem)
{
    m_container = Container(node.at("size").get<int>());
    auto slots = node.at("slots");
    for (auto it = slots.begin(); it != slots.end(); ++it)
    {
        auto res = it.value().get<std::string>();
        auto item = resSystem.get<Item>(res);
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
