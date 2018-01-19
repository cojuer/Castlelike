#include "component__reactor.h"
#include "actor.h"

const std::string ReactorComponent::stringID = "reactor";

ReactorComponent::ReactorComponent(Actor* parent) :
    ReactorComponentInterface(parent)   
{}

Json ReactorComponent::save() const
{
    // TODO: save actions
    return { { getStringID(), "" } };
}

void ReactorComponent::load(Json& node, ResourceSystem& resSystem)
{
    // TODO: load reactions
}

std::string ReactorComponent::getStringID() const
{
    return stringID;
}

void ReactorComponent::addReaction(std::string condition, Reaction&& reaction)
{
    m_reactions.insert({ condition, std::move(reaction) });
}

void ReactorComponent::react(const std::string& condition, ActionArgs input)
{
    if (!m_reactive) return;

    auto liter = m_reactions.lower_bound(condition);
    auto uiter = m_reactions.upper_bound(condition);
    for (; liter != uiter; )
    {
        // TODO: fix
		/* Combine predefined and new input parameters */
  //      auto inputCopy = input;
  //      for (auto& elem : liter->second.m_action.m_args)
  //      {
  //          inputCopy.insert(elem);
  //      }
  //      liter->second.m_action.m_act(inputCopy);
		///* Update duration of effects */
		//auto& args = liter->second.m_action.m_args;
  //  	auto durIter = args.find("duration");
		//if (durIter != args.end())
		//{
		//	auto duration = get<int>(args, "duration");
		//	args["duration"] = --duration;
		//	if (!duration)
		//	{
		//		liter = m_reactions.erase(liter);
		//		continue;
		//	}
		//}
		/* Go to the next reaction */
		++liter;
    }
}

ReactorComponent::~ReactorComponent() {}
