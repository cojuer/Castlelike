#pragma once

#include "component.h"
#include "component__graphics_interface.h"
#include "actor.h"

class ResourceManager;

class GraphicsComponent final : public GraphicsInterfaceComponent
{
public:
    static const std::string stringID;

    explicit GraphicsComponent(Actor* parent = nullptr);
	GraphicsComponent(unsigned layer, std::vector<std::string> renderableIds, Actor* parent = nullptr);

    Json save() const override;
	void load(Json& node, ResourceManager& resManager) override;

    std::string getStringID() const override;

	void setState(int state);
	std::string get() const override;

    ~GraphicsComponent();

private:
	int         m_state;
	std::vector<std::string> m_renderableIds;
};