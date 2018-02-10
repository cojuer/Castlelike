#pragma once

#include "component.h"
#include "component__graphics_interface.h"
#include "actor.h"

class ResourceSystem;

class GraphicsComponent final : public GraphicsInterfaceComponent
{
public:
    static const std::string stringID;

    explicit GraphicsComponent(Actor* parent = nullptr);
	GraphicsComponent(unsigned layer, std::vector<std::string> renderableIds, Actor* parent = nullptr);

    Json save() const override;
	void load(Json& node, ResourceSystem& resSystem) override;

    std::string getStringID() const override;

	void setState(int state);
	std::string get() const override;

private:
	int         m_state;
	std::vector<std::string> m_renderableIds;
};