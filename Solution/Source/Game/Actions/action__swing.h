#pragma once

#include "action__attack.h"

class SwingAction final : public AttackAction
{
public:
    SwingAction(ActionArgs&& args = {});

protected:
    std::vector<Actor*> getVictims() const override;
};
