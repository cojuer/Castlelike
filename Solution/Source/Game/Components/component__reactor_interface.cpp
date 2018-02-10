#include "component__reactor_interface.h"

ReactorComponentInterface::ReactorComponentInterface(Actor* parent) :
	ActorComponent(parent),
    m_reactive(true)
{}

bool ReactorComponentInterface::isReactive() const
{
	return m_reactive;
}
