#pragma once

#include "action_args.h"
#include "action_interface.h"

class MoveAction final : public ActionInterface
{
public:
    MoveAction(ActionArgs&& args = {});

    void act() override;

    void setArg(std::string argType, std::any arg) override;

    std::vector<std::string> getRequiredArgTypes() const override;

    bool canAct() const override;

private:
    ActionArgs  m_args;
};