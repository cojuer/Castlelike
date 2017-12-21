#pragma once

#include "component.h"

class ResourceManager;

class CollisionComponent final : public ActorComponent
{
public:
    static const std::string stringID;

	explicit CollisionComponent(Actor* parent = nullptr);

	void load(Json& node, ResourceManager& resManager) override;
    Json save() const override;

    std::string getStringID() const override;
 
	const bool&     get() const;
	void            set(bool collisive);

    ~CollisionComponent();

private:
	bool m_collisive;
};