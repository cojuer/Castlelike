#include "component__equipment.h"

#include "equipment.h"
#include "actor.h"

#include "item.h"
#include "resource_manager.h"

const std::string EquipmentComponent::stringID = "equipment";

EquipmentComponent::EquipmentComponent(Actor* parent) :
	ActorComponent(parent),
    m_dropped(false)
{}

EquipmentComponent::EquipmentComponent(Equipment& equipment, Actor* parent) :
	ActorComponent(parent),
	m_equipment(equipment),
    m_dropped(false)
{}

void EquipmentComponent::load(Json& node, ResourceManager& resManager)
{
	for (auto it = node.at("slots").begin(); it != node.at("slots").end(); ++it)
	{
        auto item = resManager.get<Item>(it.value().get<std::string>());
        m_equipment.equip(it.key(), *item);
	}
}

Json EquipmentComponent::save() const
{
    Json node;
    for (auto& type : Equipment::types)
    {
        if (!m_equipment.isEquipped(type)) continue;
        node["slots"][type] = m_equipment.getItem(type)->getRes();
    }
    return { { getStringID() , node } };
}

std::string EquipmentComponent::getStringID() const
{
    return stringID;
}

Equipment& EquipmentComponent::get()
{
	return m_equipment;
}

EquipmentComponent::~EquipmentComponent()
{}
