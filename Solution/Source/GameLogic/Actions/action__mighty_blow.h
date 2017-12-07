#pragma once

#include "action__attack.h"

class MightyBlowAction final : public AttackAction
{
public:
    MightyBlowAction(ActionArgs&& args = {});

    void act() override;
};
