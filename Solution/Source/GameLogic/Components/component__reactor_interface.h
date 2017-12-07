#pragma once

#include <map>

#include "action_args.h"
#include "component.h"
#include "reaction.h"

class ResourceManager;

class ReactorComponentInterface : public ActorComponent
{
public:
	explicit ReactorComponentInterface(Actor* parent = nullptr);

	virtual void react(const std::string& condition, ActionArgs input) = 0;

	bool isReactive() const;

    virtual ~ReactorComponentInterface();

protected:
	bool      m_reactive;
};
