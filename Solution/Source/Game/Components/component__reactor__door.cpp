#include "component__reactor__door.h"

#include "actor.h"
#include "scene.h"
#include "component__collision.h"
#include "component__graphics.h"

const std::string DoorReactorComponent::stringID = "reactor_door";

DoorReactorComponent::DoorReactorComponent(Actor* parent) :
	ReactorComponentInterface(parent),
	m_state(State::CLOSED)
{}

void DoorReactorComponent::load(Json& node, ResourceSystem& resSystem)
{
    m_state = static_cast<State>(node.at("state").get<int>());
	m_distance = node.at("distance").get<int>();
}

Json DoorReactorComponent::save() const
{
    Json node;
    node["state"] = static_cast<int>(m_state);
	node["distance"] = m_distance;
    return { { getStringID(), node } };
}

std::string DoorReactorComponent::getStringID() const
{
    return stringID;
}

void DoorReactorComponent::onOpened(const std::string& condition, const ActionArgs& input)
{
    auto& scene = *get<Scene*>(input, ActArgType::scene);
	auto collisionComponent = m_parent->getComponent<CollisionComponent>();
	auto graphicsComponent = m_parent->getComponent<GraphicsComponent>();

	if (condition == "on_use")
	{
		if (scene.isEmpty(m_parent->getCoord()))
		{
			m_state = State::CLOSED;
			collisionComponent->set(true);
			graphicsComponent->setState(static_cast<int>(State::CLOSED));
		}
	}
}

void DoorReactorComponent::onClosed(const std::string& condition, const ActionArgs& input)
{
	auto collisionComponent = m_parent->getComponent<CollisionComponent>();
	auto graphicsComponent = m_parent->getComponent<GraphicsComponent>();
	if (condition == "on_use")
	{
		m_state = State::OPENED;
		collisionComponent->set(false);
		graphicsComponent->setState(static_cast<int>(State::OPENED));
	}
}

void DoorReactorComponent::react(const std::string& condition, ActionArgs input)
{
	if (!m_reactive) return;

	auto& scene = *get<Scene*>(input, ActArgType::scene);
	auto coord = m_parent->getCoord();
	auto heroCoord = scene.getHero()->getCoord();
	auto heroDistance = abs(heroCoord.x - coord.x) + abs(heroCoord.y - coord.y);

	if (heroDistance <= m_distance) {
		switch (m_state)
		{
		case State::OPENED:
			onOpened(condition, std::move(input));
			break;
		case State::CLOSED:
			onClosed(condition, std::move(input));
			break;
		default:
			break;
		}
	}
}
