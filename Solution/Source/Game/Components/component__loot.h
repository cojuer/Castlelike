#pragma once

#include "container.h"

#include "component__container_interface.h"

class ResourceSystem;

class LootComponent final : public ContainerInterfaceComponent
{
public:
    static const std::string stringID;

	explicit LootComponent(Actor* parent = nullptr);
	explicit LootComponent(Container&& container, Actor* parent = nullptr);

    void generate(Json& node, ResourceSystem& resSystem) override;
	void load(Json& node, ResourceSystem& resSystem) override;
    Json save() const override;

    std::string getStringID() const override;

	Container& get();
};