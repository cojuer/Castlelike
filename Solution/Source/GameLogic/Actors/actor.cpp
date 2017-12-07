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

bool Actor::isCollisive() const
{
    auto collision = getComponent<CollisionComponent>();
    return collision ? collision->get() : false;
}

Json Actor::toJSON() const
{
    std::vector<Json> components;
    // FIXME: use auto&[] when proper support will be available
    for (const auto& pair : m_componentMap)
    {
        components.push_back(pair.second->toJSON());
    }
    Json result = components;
    return result;
}

Actor::~Actor()
{
    m_componentMap.clear();
}
