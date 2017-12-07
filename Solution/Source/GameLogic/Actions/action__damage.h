#pragma once

#include "action_args.h"
#include "action_interface.h"

class DamageAction final : public ActionInterface
{
public:
    DamageAction(ActionArgs&& args = {});

    void act() override;

    void setArg(std::string argType, std::any arg) override;

    std::vector<std::string> getRequiredArgTypes() const override;

    bool canAct() const override;

private:
    ActionArgs  m_args;
};