#include "reaction.h"

Reaction::Reaction(std::string conditionID, ActionInterface* action) :
	m_conditionID(std::move(conditionID)),
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
