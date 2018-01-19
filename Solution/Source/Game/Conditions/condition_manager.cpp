#include "condition_manager.h"

void CondMgr::init()
{}

Cond CondMgr::getCondition(const std::string& name) const
{
    return (data.find(name) != data.end() ? data.at(name) : nullptr);
}
