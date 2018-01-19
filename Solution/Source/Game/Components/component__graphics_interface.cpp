#include "component__graphics_interface.h"

GraphicsInterfaceComponent::GraphicsInterfaceComponent(unsigned layer, Actor* parent) :
	ActorComponent(parent),
	m_layer(layer)
{}

void GraphicsInterfaceComponent::setLayer(unsigned layer)
{
	m_layer = layer;
}

int GraphicsInterfaceComponent::getLayer() const
{
	return static_cast<int>(m_layer);
}

GraphicsInterfaceComponent::~GraphicsInterfaceComponent() {}
