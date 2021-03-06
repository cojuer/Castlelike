#include "component__stamina.h"

#include "actor.h"

const std::string StaminaComponent::stringID = "stamina";

StaminaComponent::StaminaComponent(Actor* parent) :
    StatComponent(0, 0, 0, parent)
{}

StaminaComponent::StaminaComponent(int base, int current, int max, Actor* parent) :
    StatComponent(base, current, max, parent)
{}

std::string StaminaComponent::getStringID() const
{
    return stringID;
}

void StaminaComponent::refresh()
{
    //getComponent<StatComponent>("health")->setCurr(attributes.at(Attr("vit")) * 6);
    //getComponent<StatComponent>("health")->setMax(attributes.at(Attr("vit")) * 6);
}
