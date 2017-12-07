#pragma once

#include <map>

#include "action_args.h"
#include "action_interface.h"

class ActMgr
{
public:
    void          init();

    ActionArgs    getNeeded(std::string name) const;
    ActionInterface* getAction(std::string name, ActionArgs&& args = {}) const;

private:
    std::map<std::string, ActionInterface*(*)(ActionArgs&& args)> data;
    std::map<std::string, ActionArgs> input;
};