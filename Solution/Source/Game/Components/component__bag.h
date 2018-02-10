#pragma once

#include "container.h"

#include "component__container_interface.h"

class ResourceSystem;

class BagComponent final : public ContainerInterfaceComponent
{
public:
    static const std::string stringID;

	explicit BagComponent(Actor* parent = nullptr);
	explicit BagComponent(Container&& container, Actor* parent = nullptr);

	void load(Json& node, ResourceSystem& resSystem) override;
    Json save() const override;

    std::string getStringID() const override;

	Container& get();

    bool isDropped() const;

private:
    bool       m_dropped;
};