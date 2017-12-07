#pragma once

#include "component__health.h"
#include "actor.h"

const std::string HealthComponent::stringID = "health";

HealthComponent::HealthComponent(Actor* parent) :
	StatComponent(0, 0, 0, parent)
{}

HealthComponent::HealthComponent(int base, int current, int max, Actor* parent) :
	StatComponent(base, current, max, parent)
{}

void HealthComponent::fromJSON(Json& node, ResourceManager& resManager)
{
	m_base = node[0];
    m_current = node[1];
    m_max = node[2];
}

std::string HealthComponent::getStringID() const
{
    return stringID;
}

void HealthComponent::refresh()
{
	//getComponent<StatComponent>("health")->setCurr(attributes.at(Attr("vit")) * 6);
	//getComponent<StatComponent>("health")->setMax(attributes.at(Attr("vit")) * 6);
}

HealthComponent::~HealthComponent() {}
