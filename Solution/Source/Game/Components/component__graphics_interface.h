#pragma once

#include "component.h"

class GraphicsInterfaceComponent : public ActorComponent
{
public:
	explicit GraphicsInterfaceComponent(unsigned layer, Actor* parent = nullptr);
    
    GraphicsInterfaceComponent(const GraphicsInterfaceComponent&) = delete;
    GraphicsInterfaceComponent(GraphicsInterfaceComponent&&) = delete;
    GraphicsInterfaceComponent& operator=(const GraphicsInterfaceComponent&) = delete;
    GraphicsInterfaceComponent& operator=(GraphicsInterfaceComponent&&) = delete;

    virtual ~GraphicsInterfaceComponent();

	void                setLayer(unsigned layer);

	int					getLayer() const;
	virtual std::string get() const = 0;

protected:
	uint32_t m_layer;
};