#pragma once

#include <map>

#include "condition.h"

class CondMgr
{
public:
    void          init();

    Cond          getCondition(const std::string& name) const;

private:
    std::map<std::string, Cond> data;
    std::map<std::string, CondInput> input;
};