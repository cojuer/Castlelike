#include "component__attr.h"
#include "actor.h"

const std::string AttrComponent::stringID = "attributes";

AttrComponent::AttrComponent(Actor* parent) :
    ActorComponent(parent),
	m_points(0)
{}

AttrComponent::AttrComponent(Attributes attrs, Actor* parent) :
	ActorComponent(parent),
	m_attrs(std::move(attrs)),
	m_points(0)
{}

void AttrComponent::load(Json& node, ResourceSystem& resSystem)
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
    for (auto&[type, data] : m_attrs.data())
    {
        node[type] = data;
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
