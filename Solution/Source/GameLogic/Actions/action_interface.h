#pragma once

#include <any>
#include <string>
#include <vector>

#include "action_args.h"

class ActionInterface
{
public:
    virtual ~ActionInterface() = default;

    virtual void act() = 0;

    virtual void setArg(std::string, std::any arg) = 0;

    virtual std::vector<std::string> getRequiredArgTypes() const = 0;

    virtual bool canAct() const = 0;
};

template<typename T>
ActionInterface* createAction(ActionArgs&& args = {})
{
    return new T{ std::move(args) };
}