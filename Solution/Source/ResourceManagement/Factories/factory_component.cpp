#include "factory_component.h"

#include <iostream>

#include "components.h"

ComponentFactory::ComponentFactory() :
    m_resManager(nullptr)
{
    m_map[AIComponent::stringID] =         &ActorComponent::create<AIComponent>;
    m_map[PlayerComponent::stringID] =     &ActorComponent::create<PlayerComponent>;
    m_map[PositionComponent::stringID] =   &ActorComponent::create<PositionComponent>;
    m_map[CollisionComponent::stringID] =  &ActorComponent::create<CollisionComponent>;
    m_map[AttrComponent::stringID] =       &ActorComponent::create<AttrComponent>;
    m_map[GraphicsComponent::stringID] =   &ActorComponent::create<GraphicsComponent>;
    m_map[HealthComponent::stringID] =     &ActorComponent::create<HealthComponent>;
    m_map[MdfrComponent::stringID] =       &ActorComponent::create<MdfrComponent>;
    m_map[LootComponent::stringID] =       &ActorComponent::create<LootComponent>;
    m_map[WeightComponent::stringID] =     &ActorComponent::create<WeightComponent>;
    m_map[TransformComponent::stringID] =  &ActorComponent::create<TransformComponent>;
    m_map[ActionPtsComponent::stringID] =  &ActorComponent::create<ActionPtsComponent>;
}

bool ComponentFactory::init(ResourceManager& resManager)
{
    m_resManager = &resManager;
    return true;
}

bool ComponentFactory::load(const std::string& fname)
{
    return m_loader.load(fname);
}

Resource<ActorComponent>* ComponentFactory::get(ResourceId& id)
{
    auto node = m_loader.get("/" + id);
    if (node)
    {
        auto type = id.substr(id.find_last_of('/') + 1);
        auto typeIt = m_map.find(type);
        if (typeIt == m_map.end())
        {
            std::cout << "Component factory: component type "
                << type << " is not supported" << std::endl;
        }
        else
        {
            auto component = m_map[type]();
            component->fromJSON(*node, *m_resManager);
            return component;
        }
    }
    // FIXME: use nullptr and pointers
    return nullptr;
}
