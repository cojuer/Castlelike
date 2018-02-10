#pragma once

#include "component__stat.h"
#include "actor.h"

class WeightComponent final : public StatComponent
{
public:
    static const std::string stringID;

    explicit WeightComponent(Actor* parent = nullptr);
    WeightComponent(int base, int current, int max, Actor* parent = nullptr);

    std::string getStringID() const override;
};
