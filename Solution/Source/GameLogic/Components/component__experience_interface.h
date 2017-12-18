#pragma once

#include "component.h"

class  ResourceManager;

class ExperienceInterfaceComponent : public ActorComponent
{
public:
	explicit ExperienceInterfaceComponent(Actor* parent = nullptr);
	ExperienceInterfaceComponent(int level, int xp, Actor* parent = nullptr);

    Json save() const override;
	void load(Json& node, ResourceManager& resManager) override;

	void addXP(int xp);
    void setXpToLvlUp(int xpToLvlUp);

	const int& getXp() const;
	const int& getXpToLvlUp() const;
	const int& getLevel() const;

    void updateLvl();

    virtual int countXpToLvlUp(int level) const = 0;

    virtual ~ExperienceInterfaceComponent();

protected:
    int m_level;
	int m_xp;
	int m_xpToLvlUp;
};