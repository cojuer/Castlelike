#pragma once

#include "component__stat.h"
#include "actor.h"

class StaminaComponent final : public StatComponent
{
public:
    static const std::string stringID;

    explicit StaminaComponent(Actor* parent = nullptr);
    StaminaComponent(int base, int current, int max, Actor* parent = nullptr);

    std::string getStringID() const override;

    void refresh() override;

    ~StaminaComponent();
};
