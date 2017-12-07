#include "component__equipment.h"

#include "equipment.h"
#include "actor.h"

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

void EquipmentComponent::fromJSON(Json& node, ResourceManager& resManager)
{
	// non-loadable
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
