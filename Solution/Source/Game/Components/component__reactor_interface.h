#pragma once

#include <map>

#include "action_args.h"
#include "component.h"

class ResourceSystem;

class ReactorComponentInterface : public ActorComponent
{
public:
	explicit ReactorComponentInterface(Actor* parent = nullptr);

    ReactorComponentInterface(const ReactorComponentInterface&) = delete;
    ReactorComponentInterface(ReactorComponentInterface&&) = delete;
    ReactorComponentInterface& operator=(const ReactorComponentInterface&) = delete;
    ReactorComponentInterface& operator=(ReactorComponentInterface&&) = delete;

    virtual ~ReactorComponentInterface() = default;

	virtual void react(const std::string& condition, ActionArgs input) = 0;

	bool isReactive() const;

protected:
	bool      m_reactive;
};
