#include "component__attr.h"
#include "actor.h"

const std::string AttrComponent::stringID = "attributes";

AttrComponent::AttrComponent(Actor* parent) :
    ActorComponent(parent),
	m_points(0)
{}

AttrComponent::AttrComponent(const Attributes& attrs, Actor* parent) :
	ActorComponent(parent),
	m_attrs(attrs),
	m_points(0)
{}

void AttrComponent::load(Json& node, ResourceManager& resManager)
{
	for (auto& type : Attributes::types)
	{
		auto attribute = node[type];
        if (!attribute.is_null())
        {
            m_attrs[type] = static_cast<int>(attribute);
        }
	}
}

Json AttrComponent::save() const
{
    Json node;
    for (auto pair : m_attrs.data())
    {
        node[pair.first] = pair.second;
    }
    return { { getStringID(), node } };
}

std::string AttrComponent::getStringID() const
{
    return stringID;
}

const Attributes& AttrComponent::get() const
{
    return m_attrs;
}

AttrComponent::~AttrComponent()
{}
