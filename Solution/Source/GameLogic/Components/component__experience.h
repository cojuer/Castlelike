#pragma once

#include "component__experience_interface.h"

class  ResourceManager;

class ExperienceComponent final : public ExperienceInterfaceComponent
{
public:
    static const std::string stringID;

    explicit ExperienceComponent(Actor* parent = nullptr);
    ExperienceComponent(int level, int xp, Actor* parent = nullptr);

    std::string getStringID() const override;

    ~ExperienceComponent();

private:
    int countXpToLvlUp(int level) const override;
};