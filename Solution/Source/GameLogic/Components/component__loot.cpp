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
    for (auto& itemNode : node)
    {
        std::string name = itemNode["name"];
        int minItems = itemNode["min"];
        int maxItems = itemNode["max"];
        int chance = itemNode["chance"];
        // TODO: add multiple items in stacks if possible
        for (auto i = 0; i < maxItems; ++i)
        {
            if (i < minItems || m_lootRng.getInRange(0, 100) <= chance)
            {
                auto item = resManager.get<Item>(name);
                assert(item);
                if (item)
                {
                    m_container.add(*item);
                }
            }
        }
    }
}

Json LootComponent::toJSON() const
{
    Json node;
    auto& slots = m_container.m_busyslots;
    for (auto& pair : slots)
    {
        node[pair.first] = pair.second->getRes();
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
