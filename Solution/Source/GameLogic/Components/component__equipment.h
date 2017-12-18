#pragma once

#include "component.h"
#include "equipment.h"

class ResourceManager;

class EquipmentComponent final : public ActorComponent
{
public:
    static const std::string stringID;

	explicit EquipmentComponent(Actor* parent = nullptr);
	explicit EquipmentComponent(Equipment& equipment, Actor* parent = nullptr);

	void fromJSON(Json& node, ResourceManager& resManager) override;
    Json toJSON() const override;
    std::string getStringID() const override;

	Equipment& get();

    ~EquipmentComponent();

private:
	Equipment  m_equipment;
    bool       m_dropped;
};