#pragma once

#include <map>

#include "component__reactor_interface.h"

class ResourceSystem;

class DialReactorComponent : public ReactorComponentInterface
{
public:
	static const std::string stringID;

	explicit DialReactorComponent(Actor* parent = nullptr);
	explicit DialReactorComponent(int id, Actor* parent = nullptr);

	void load(Json& node, ResourceSystem& resSystem) override;
	Json save() const override;

	std::string getStringID() const override;

	void react(const std::string& condition, ActionArgs input) override;

private:
	void onClick();

private:
	int m_id;
};