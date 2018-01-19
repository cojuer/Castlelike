#pragma once

#include <map>

#include "actor.h"
#include "component__reactor_interface.h"

class ResourceSystem;

class DoorReactorComponent : public ReactorComponentInterface
{
	enum class State
	{
		CLOSED = 0,
		OPENED = 1
	};

public:
    static const std::string stringID;

	explicit DoorReactorComponent(Actor* parent = nullptr);

	void load(Json& node, ResourceSystem& resSystem) override;
    Json save() const override;

    std::string getStringID() const override;

	void react(const std::string& condition, ActionArgs input) override;

    ~DoorReactorComponent();

private:
	void onOpened(const std::string& condition, ActionArgs input);
	void onClosed(const std::string& condition, ActionArgs input);

private:
	State     m_state;
};