#include "actor.h"

#include "component.h"
#include "component__collision.h"
#include "component__position.h"

Actor::Actor(ActorID id, const std::string& resID) :
    m_id(id),
	m_res(resID)
{}

Actor::Actor(ActorID id, const std::string& resID, const std::string& type, Coord pos, bool collisive) :
    m_id(id),
    m_res(resID),
    m_type(type)
{
	auto posComponent = new PositionComponent();
	posComponent->set(pos);
	addComponent<PositionComponent>(*posComponent);

	auto colComponent = new CollisionComponent();
	colComponent->set(collisive);
	addComponent<CollisionComponent>(*colComponent);
}

void Actor::setCoord(Coord coord)
{
	getComponent<PositionComponent>()->set(coord);
}

ActorID Actor::getID() const
{
    return m_id;
}

const std::string& Actor::getRes() const
{
    return m_res;
}

const Coord& Actor::getCoord() const
{
	return getComponent<PositionComponent>()->get();
}

const std::string& Actor::getType() const
{
    return m_type;
}

std::vector<ActorComponent*> Actor::getComponents() const
{
    std::vector<ActorComponent*> result;
    for (const auto&[id, component] : m_componentMap)
    {
        result.push_back(component);
    }
    return result;
}

bool Actor::isCollisive() const
{
    auto collision = getComponent<CollisionComponent>();
    return collision ? collision->get() : false;
}

Json Actor::toJSON() const
{
    Json components;
    for (const auto& [id, component] : m_componentMap)
    {
        auto compJson = component->save();
        assert(!compJson.is_null() && "component saves to null");
        assert(compJson.is_object() && "invalid Json for component");
        // TODO: delete cycle
        for (auto it = compJson.begin(); 
                  it != compJson.end(); ++it)
        {
            components[it.key()] = it.value();
        }
    }
    Json result = 
    {
        { "id", m_id },
        { "res", m_res },
        { "type", m_type },
        { "components", components }
    };
    return result;
}

Actor::~Actor()
{
    m_componentMap.clear();
}
