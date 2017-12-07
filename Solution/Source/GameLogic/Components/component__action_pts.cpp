#pragma once

#include "component__action_pts.h"
#include "actor.h"

const std::string ActionPtsComponent::stringID = "action_pts";

ActionPtsComponent::ActionPtsComponent(Actor* parent) :
    StatComponent(0, 0, 0, parent)
{}

ActionPtsComponent::ActionPtsComponent(int base, int current, int max, Actor* parent) :
    StatComponent(base, current, max, parent)
{}

void ActionPtsComponent::fromJSON(Json& node, ResourceManager& resManager)
{
    m_base = node[0];
    m_current = node[1];
    m_max = node[2];
}

std::string ActionPtsComponent::getStringID() const
{
    return stringID;
}

ActionPtsComponent::~ActionPtsComponent() {}
