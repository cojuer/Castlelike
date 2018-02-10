#pragma once

#include "component__stat.h"
#include "actor.h"

class ActionPtsComponent final : public StatComponent
{
public:
    static const std::string stringID;

    explicit ActionPtsComponent(Actor* parent = nullptr);
    ActionPtsComponent(int base, int current, int max, Actor* parent = nullptr);
    
    std::string getStringID() const override;
};
