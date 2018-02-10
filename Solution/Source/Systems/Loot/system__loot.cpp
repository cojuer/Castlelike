#include "system__loot.h"

#include "scene.h"
#include "container.h"
#include "actor__storage.h"

#include "system__actor_id.h"
#include "system__scene.h"
#include "system__actor_registrar.h"

#include "component__health.h"
#include "component__loot.h"

bool LootGSystem::init(ActorRegistrar& actorRegistrar, SceneSystem& sceneSystem)
{
    m_actorRegistrar = &actorRegistrar;
    m_sceneSystem = &sceneSystem;
    return true;
}

bool LootGSystem::reg(Actor& actor)
{
    auto hpComponent = actor.getComponent<HealthComponent>();
    if (hpComponent)
    {
        m_registered.insert(std::make_pair(actor.getID(), &actor));
        return true;
    }
    return false;
}

void LootGSystem::unreg(ActorID id)
{
    m_registered.erase(id);
}

void LootGSystem::update()
{
    for (auto iter = m_registered.begin(); iter != m_registered.end();)
    {
        auto actor = iter->second;
        if (m_registered.find(actor->getID()) == m_registered.end()) continue;

        auto hpComponent = actor->getComponent<HealthComponent>();
        auto lootComp = actor->getComponent<LootComponent>();

        // Registered actor always has hpComponent
        if (hpComponent->getCurr() <= 0)
        { 
            auto coord = actor->getCoord();
            auto scene = m_sceneSystem->getScene();
            // FIXME: no Storage Actors after loading
            auto areaCont = dynamic_cast<StorageActor*>(scene->getActor(coord, ActorType::CONTAINER));
            if (!areaCont)
            {
                Container cont{ 36 };
                if (lootComp)
                {
                    cont.takeFrom(lootComp->get());
                }
                areaCont = new StorageActor(IDManager::instance().getActorID(), coord, actor->getRes() + "_remains", false, std::move(cont), false);
                scene->addActor(*areaCont);
                m_actorRegistrar->reg(*areaCont);
            }
            else if (lootComp)
            {
                areaCont->getContainer().takeFrom(lootComp->get());
            }
            iter = m_registered.erase(iter);
            m_actorRegistrar->unreg(actor->getID());
            m_sceneSystem->getScene()->delActor(*actor);
        }
        else ++iter;
    }
}

void LootGSystem::clean()
{
    m_registered.clear();
}
