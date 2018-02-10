#include "action__heal.h"

#include "actor.h"
#include "component__health.h"

HealAction::HealAction(ActionArgs&& args) :
    m_args(std::move(args))
{}

void HealAction::act()
{
    auto& user = *get<Actor*>(m_args, ActArgType::user);
    auto power = get<int>(m_args, ActArgType::power);

    auto hpComponent = user.getComponent<HealthComponent>();
    if (hpComponent)
    {
        hpComponent->changeCurrent(power);
    }
}

void HealAction::setArg(std::string argType, std::any arg)
{
    m_args[argType] = arg;
}

std::vector<std::string> HealAction::getRequiredArgTypes() const
{
    std::vector<std::string> allArgTypesNeeded = {
        ActArgType::user,
        ActArgType::power
    };
    std::vector<std::string> argTypesNeeded;
    for (auto& type : allArgTypesNeeded)
    {
        if (m_args.find(type) == m_args.end())
        {
            argTypesNeeded.push_back(type);
        }
    }
    return argTypesNeeded;
}

bool HealAction::canAct() const
{
    return getRequiredArgTypes().empty();
}
