#pragma once

#include "action_interface.h"

struct Reaction
{
public: 
	Reaction(const std::string conditionID, ActionInterface* action);

    std::string      getConditionID() const;
    ActionInterface* getAction() const;

private:
    std::string      m_conditionID;
    ActionInterface* m_action;
};
