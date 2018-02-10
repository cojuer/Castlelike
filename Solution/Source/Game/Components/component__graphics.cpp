#include "component__graphics.h"

#include "system__resource.h"
#include "actor.h"

const std::string GraphicsComponent::stringID = "graphics";

GraphicsComponent::GraphicsComponent(unsigned layer, std::vector<std::string> renderableIds, Actor* parent) :
    GraphicsInterfaceComponent(layer, parent), 
    m_state(0),
    m_renderableIds(std::move(renderableIds))
{}

GraphicsComponent::GraphicsComponent(Actor* parent) :
    GraphicsInterfaceComponent(0, parent), 
    m_state(0)
{}

Json GraphicsComponent::save() const
{
    Json node;
    node["layer"] = m_layer;
    for (auto rendID : m_renderableIds)
    {
        node["sprites"].push_back(rendID);
    }
    return { { getStringID(), node } };
}

void GraphicsComponent::load(Json& node, ResourceSystem& resSystem)
{
    m_state = 0;
    m_layer = node["layer"];
    for (auto& rendNode : node["sprites"])
    {
        m_renderableIds.push_back(rendNode.get<std::string>());
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
