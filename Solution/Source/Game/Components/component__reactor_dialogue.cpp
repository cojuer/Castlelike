#include "component__reactor_dialogue.h"

#include "actor.h"
#include "scene.h"
#include "component__collision.h"
#include "component__graphics.h"
#include "subsystem__event.h"
#include "event__dialogue.h"

const std::string DialReactorComponent::stringID = "reactor_dl";

DialReactorComponent::DialReactorComponent(Actor* parent) :
	ReactorComponentInterface(parent),
	m_id(-1)
{}

DialReactorComponent::DialReactorComponent(int id, Actor* parent) :
	ReactorComponentInterface(parent),
	m_id(id)
{}

void DialReactorComponent::load(Json& node, ResourceSystem& resSystem)
{
	m_id = node.at("id").get<int>();
	m_distance = node.at("distance").get<int>();
}

Json DialReactorComponent::save() const
{
	Json node;
	node["id"] = static_cast<int>(m_id);
	node["distance"] = m_distance;
	return { { getStringID(), node } };
}

std::string DialReactorComponent::getStringID() const
{
	return stringID;
}

void DialReactorComponent::onClick()
{
	auto event = new DlEvent(DlEvType::START_DL, 0, nullptr, m_id);
	EventSubsystem::FireEvent(*event);
}

void DialReactorComponent::react(const std::string& condition, ActionArgs input)
{
	if (!m_reactive) return;

	auto& scene = *get<Scene*>(input, ActArgType::scene);

	auto coord = m_parent->getCoord();
	auto heroCoord = scene.getHero()->getCoord();
	auto heroDistance = abs(heroCoord.x - coord.x) + abs(heroCoord.y - coord.y);

	if (heroDistance <= m_distance) {
		onClick();
	}
}
