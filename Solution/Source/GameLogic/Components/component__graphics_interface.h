#pragma once

#include "component.h"

class GraphicsInterfaceComponent : public ActorComponent
{
public:
	explicit GraphicsInterfaceComponent(unsigned layer, Actor* parent = nullptr);
    
	void                setLayer(unsigned layer);

	int					getLayer() const;
	virtual std::string get() const = 0;

    virtual ~GraphicsInterfaceComponent();

protected:
	unsigned            m_layer;
};