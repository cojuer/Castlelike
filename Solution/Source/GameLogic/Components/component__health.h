#pragma once

#include "component__stat.h"
#include "actor.h"

class HealthComponent final : public StatComponent
{
public:
    static const std::string stringID;

	explicit HealthComponent(Actor* parent = nullptr);
	HealthComponent(int base, int current, int max, Actor* parent = nullptr);

	void fromJSON(Json& node, ResourceManager& resManager) override;
    std::string getStringID() const override;

	void refresh() override;

    ~HealthComponent();
};
