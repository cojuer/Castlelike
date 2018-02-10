#pragma once

#include "component.h"

class  ResourceSystem;

class ExperienceInterfaceComponent : public ActorComponent
{
public:
	explicit ExperienceInterfaceComponent(Actor* parent = nullptr);
	ExperienceInterfaceComponent(int level, int xp, Actor* parent = nullptr);

    ExperienceInterfaceComponent(const ExperienceInterfaceComponent&) = delete;
    ExperienceInterfaceComponent(ExperienceInterfaceComponent&&) = delete;
    ExperienceInterfaceComponent& operator=(const ExperienceInterfaceComponent&) = delete;
    ExperienceInterfaceComponent& operator=(ExperienceInterfaceComponent&&) = delete;

    virtual ~ExperienceInterfaceComponent();

    Json save() const override;
	void load(Json& node, ResourceSystem& resSystem) override;

	void addXP(int xp);
    void setXpToLvlUp(int xpToLvlUp);

	const int& getXp() const;
	const int& getXpToLvlUp() const;
	const int& getLevel() const;

    void updateLvl();

    virtual int countXpToLvlUp(int level) const = 0;

protected:
    int m_level;
	int m_xp;
	int m_xpToLvlUp;
};