#include "factory_actor.h"

#include <iostream>

#include "components.h"
#include "resource_manager.h"
#include "id_manager.h"

bool ActorFactory::init(ResourceManager& resManager)
{
    m_resManager = &resManager;
    regToAddCompMap<AIComponent>(AIComponent::stringID);
    regToAddCompMap<AttrComponent>(AttrComponent::stringID);
    regToAddCompMap<MdfrComponent>(MdfrComponent::stringID);
    regToAddCompMap<PositionComponent>(PositionComponent::stringID);
    regToAddCompMap<GraphicsInterfaceComponent>(GraphicsComponent::stringID);
    regToAddCompMap<HealthComponent>(HealthComponent::stringID);
    regToAddCompMap<WeightComponent>(WeightComponent::stringID);
    regToAddCompMap<LootComponent>(LootComponent::stringID);
    regToAddCompMap<CollisionComponent>(CollisionComponent::stringID);
    regToAddCompMap<TransformComponent>(TransformComponent::stringID);
    regToAddCompMap<ActionPtsComponent>(ActionPtsComponent::stringID);
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
    auto& node = *m_loader.get("/" + name);
    if (node.is_null()) return nullptr;
 
    // FIXME: use id manager
    auto& actor = *new Actor(IDManager::instance().getActorID(), name);
    for (auto it = node.begin(); it != node.end(); ++it)
    {
        auto jsonPtr = name + std::string("/") + it.key();
        auto component = m_resManager->get<ActorComponent>(jsonPtr);
        if (component)
        {
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
    
    return &actor;
}

ActorFactory::~ActorFactory() {}
