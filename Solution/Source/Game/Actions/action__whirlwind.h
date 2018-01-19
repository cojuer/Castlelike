#pragma once

#include "action__attack.h"

class WhirlwindAction final : public AttackAction
{
public:
    WhirlwindAction(ActionArgs&& args = {});

    std::vector<std::string> getRequiredArgTypes() const override;

    bool canAct() const override;

protected:
    std::vector<Actor*> getVictims() const override;
};
