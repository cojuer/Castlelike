#include "reaction.h"

Reaction::Reaction(const std::string conditionID, ActionInterface* action) :
	m_conditionID(conditionID),
	m_action(action)
{}

std::string Reaction::getConditionID() const
{
    return m_conditionID;
}

ActionInterface* Reaction::getAction() const
{
    return m_action;
}
