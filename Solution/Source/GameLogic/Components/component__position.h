#pragma once

#include "component.h"
#include "vec2.h"

class ResourceManager;

class PositionComponent final : public ActorComponent
{
public:
    static const std::string stringID;

	explicit PositionComponent(Actor* parent = nullptr);

    Json toJSON() const override;
	void fromJSON(Json& node, ResourceManager& resManager) override;
    std::string getStringID() const override;

	const Coord&    get() const;
	void            set(Coord position);

    ~PositionComponent();

private:
	Coord m_position;
};