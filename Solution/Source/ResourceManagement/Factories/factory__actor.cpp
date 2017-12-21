#include "factory__actor.h"

#include <iostream>

#include "components.h"
#include "resource_manager.h"
#include "id_manager.h"
#include "factory__component.h"

bool ActorFactory::init(ResourceManager& resManager)
{
    m_resManager = &resManager;
    regToAddCompMap<AIComponent>(AIComponent::stringID);
    regToAddCompMap<PlayerComponent>(PlayerComponent::stringID);
    regToAddCompMap<AttrComponent>(AttrComponent::stringID);
    regToAddCompMap<MdfrComponent>(MdfrComponent::stringID);
    regToAddCompMap<PositionComponent>(PositionComponent::stringID);
    regToAddCompMap<GraphicsInterfaceComponent>(GraphicsComponent::stringID);
    regToAddCompMap<HealthComponent>(HealthComponent::stringID);
    regToAddCompMap<StaminaComponent>(StaminaComponent::stringID);
    regToAddCompMap<ExperienceInterfaceComponent>(ExperienceComponent::stringID);
    regToAddCompMap<WeightComponent>(WeightComponent::stringID);
    regToAddCompMap<BagComponent>(BagComponent::stringID);
    regToAddCompMap<LootComponent>(LootComponent::stringID);
    regToAddCompMap<CollisionComponent>(CollisionComponent::stringID);
    regToAddCompMap<TransformComponent>(TransformComponent::stringID);
    regToAddCompMap<ActionPtsComponent>(ActionPtsComponent::stringID);
    regToAddCompMap<EquipmentComponent>(EquipmentComponent::stringID);
    return true;
}

template <typename T>
void ActorFactory::regToAddCompMap(std::string strCompId)
{
    addComp[strCompId] = &Actor::addComponent<T>;
}

bool ActorFactory::load(const std::string& fname)
{
    return m_loader.load(fname);
}

Resource<Actor>* ActorFactory::get(ResourceId& name)
{
    // FIXME: loader can return nullptr
    auto& node = *m_loader.get("/" + name);
    if (node.is_null()) return nullptr;

    auto& actor = *new Actor(IDManager::instance().getActorID(), name);

    loadComp(node, actor);
    postLoadComp(actor);
    
    return &actor;
}

Resource<Actor>* ActorFactory::createActorFromJSON(Json& node)
{
    if (node.is_null()) return nullptr;

    auto id = node.at("id").get<long long>();
    auto name = node.at("res").get<std::string>();

    auto& actor = *new Actor{ id, name };

    loadComp(node, actor);
    postLoadComp(actor);

    return &actor;
}

ActorFactory::~ActorFactory() {}

void ActorFactory::loadComp(const Json& node, Actor& actor)
{
    auto components = node.at("components");
    auto compFactory = m_resManager->m_componentFactory.get();
    for (auto it = components.begin(); it != components.end(); ++it)
    {
        auto compName = it.key();
        auto compNode = it.value();
        auto component = compFactory->generateCompFromJSON(compName, compNode);
        if (!component) continue;

        auto compIt = addComp.find(it.key());
        if (compIt == addComp.end())
        {
            std::cout << "Actor factory: component type "
                      << it.key() << " is not supported" << std::endl;
        }
        else
        {
            (actor.*addComp[it.key()])(*component);
        }
    }
}

void ActorFactory::postLoadComp(Actor& actor)
{
    for (auto component : actor.getComponents())
    {
        component->postGenerate(*m_resManager);
    }
}

