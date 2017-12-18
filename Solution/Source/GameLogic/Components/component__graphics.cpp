#include "component__graphics.h"

#include "resource_manager.h"
#include "actor.h"

const std::string GraphicsComponent::stringID = "graphics";

GraphicsComponent::GraphicsComponent(unsigned layer, std::vector<std::string> renderableIds, Actor* parent) :
    GraphicsInterfaceComponent(layer, parent), 
    m_state(0),
    m_renderableIds(renderableIds)
{}

GraphicsComponent::GraphicsComponent(Actor* parent) :
    GraphicsInterfaceComponent(0, parent), 
    m_state(0)
{}

Json GraphicsComponent::toJSON() const
{
    Json node;
    node["layer"] = m_layer;
    for (auto rendID : m_renderableIds)
    {
        node["sprites"].push_back(rendID);
    }
    return { { getStringID(), node } };
}

void GraphicsComponent::fromJSON(Json& node, ResourceManager& resManager)
{
    m_state = 0;
    m_layer = node["layer"];
    for (auto& rendNode : node["sprites"])
    {
        m_renderableIds.push_back(rendNode);
    }
}

std::string GraphicsComponent::getStringID() const
{
    return stringID;
}

void GraphicsComponent::setState(int state)
{
	m_state = state;
}

std::string GraphicsComponent::get() const
{
	return m_renderableIds.at(m_state);
}

GraphicsComponent::~GraphicsComponent() {}
