#include "component__weight.h"

#include "actor.h"

const std::string WeightComponent::stringID = "weight";

WeightComponent::WeightComponent(Actor* parent) :
    StatComponent(0, 0, 0, parent)
{}

WeightComponent::WeightComponent(int base, int current, int max, Actor* parent) :
    StatComponent(base, current, max, parent)
{}

std::string WeightComponent::getStringID() const
{
    return stringID;
}
