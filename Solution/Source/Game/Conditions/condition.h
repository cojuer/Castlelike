#pragma once

#include <map>
#include <vector>
#include <string>
#include <any>

class Actor;

using CondInput = std::map<std::string, std::any>;
using Cond = bool(*)(CondInput&);

struct Condition
{
    Condition(Cond, CondInput* args = nullptr);

    Cond       action;
    CondInput* args;
};

namespace condition
{
    
bool always(CondInput&);
bool has_item(CondInput&);

}
