#pragma once

#include "container.h"
#include "rng.h"

#include "component__container_interface.h"

class ResourceManager;

class LootComponent final : public ContainerInterfaceComponent
{
public:
    static const std::string stringID;

	explicit LootComponent(Actor* parent = nullptr);
	explicit LootComponent(Container& container, Actor* parent = nullptr);

	void load(Json& node, ResourceManager& resManager) override;
    Json save() const override;
    std::string getStringID() const override;

	Container& get();

    ~LootComponent();

private:
    static RNG m_lootRng;
};