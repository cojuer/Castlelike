#include "factory__actor.h"

#include <iostream>

#include "components.h"
#include "system__resource.h"
#include "system__actor_id.h"
#include "factory__component.h"

bool ActorFactory::init(ResourceSystem& resSystem)
{
    m_resSystem = &resSystem;
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
    regToAddCompMap<ReactorComponentInterface>(ReactorComponent::stringID);
    regToAddCompMap<ReactorComponentInterface>(DoorReactorComponent::stringID);
    regToAddCompMap<ReactorComponentInterface>(DialReactorComponent::stringID);
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
    auto type = node.at("type").get<std::string>();

    auto& actor = *new Actor(IDManager::instance().getActorID(), name, type);

    generateComps(node, actor);
    postGenerateComps(actor);
    
    return &actor;
}

Resource<Actor>* ActorFactory::generateActor(Json& node)
{
    if (node.is_null()) return nullptr;

    auto id = node.at("id").get<long long>();
    auto name = node.at("res").get<std::string>();
    auto type = node.at("type").get<std::string>();

    auto& actor = *new Actor{ id, name, type };

    generateComps(node, actor);
    postGenerateComps(actor);

    return &actor;
}

Resource<Actor>* ActorFactory::loadActor(Json& node)
{
    if (node.is_null()) return nullptr;

    auto id = node.at("id").get<long long>();
    auto name = node.at("res").get<std::string>();
    auto type = node.at("type").get<std::string>();

    auto& actor = *new Actor{ id, name, type };

    loadComps(node, actor);
    postLoadComps(actor);

    return &actor;
}

void ActorFactory::generateComps(const Json& node, Actor& actor)
{
    auto components = node.at("components");
    auto compFactory = m_resSystem->m_componentFactory.get();
    for (auto it = components.begin(); it != components.end(); ++it)
    {
        auto compName = it.key();
        auto compNode = it.value();
        auto component = compFactory->generateComp(compName, compNode);
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

void ActorFactory::loadComps(const Json& node, Actor& actor)
{
    auto components = node.at("components");
    auto compFactory = m_resSystem->m_componentFactory.get();
    for (auto it = components.begin(); it != components.end(); ++it)
    {
        auto compName = it.key();
        auto compNode = it.value();
        auto component = compFactory->loadComp(compName, compNode);
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

void ActorFactory::postGenerateComps(Actor& actor)
{
    for (auto component : actor.getComponents())
    {
        component->postGenerate(*m_resSystem);
    }
}

void ActorFactory::postLoadComps(Actor& actor)
{
    for (auto component : actor.getComponents())
    {
        component->postLoad(*m_resSystem);
    }
}

