#pragma once

#include "container.h"

#include "component__container_interface.h"

class ResourceManager;

class BagComponent final : public ContainerInterfaceComponent
{
public:
    static const std::string stringID;

	explicit BagComponent(Actor* parent = nullptr);
	explicit BagComponent(Container& container, Actor* parent = nullptr);

	void fromJSON(Json& node, ResourceManager& resManager) override;
    Json toJSON() const override;
    std::string getStringID() const override;

	Container& get();

    bool isDropped() const;

    ~BagComponent();

private:
    bool       m_dropped;
};