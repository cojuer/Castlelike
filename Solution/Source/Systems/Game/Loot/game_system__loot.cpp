#include "game_system__loot.h"

#include "scene.h"
#include "container.h"
#include "actor__storage.h"

#include "system__actor_id.h"
#include "system__scene.h"
#include "game_system_manager.h"

#include "component__bag.h"
#include "component__equipment.h"
#include "component__health.h"
#include "component__loot.h"

bool LootGSystem::init(GameSystemManager& sysManager, SceneSystem& sceneSystem)
{
    m_sceneSystem = &sceneSystem;
    m_sysManager = &sysManager;
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
            auto areaCont = dynamic_cast<StorageActor*>(scene->getActor(coord, ActorType::CONTAINER));
            Container* cont = nullptr;
            if (!areaCont)
            {
                if (lootComp)
                {
                    // FIXME: 2 containers have ownership
                    cont = new Container(lootComp->get());
                }
                else
                {
                    // FIXME: no loot = no container
                    cont = new Container(36);
                }
                areaCont = new StorageActor(IDManager::instance().getActorID(), coord, actor->getRes() + "_remains", false, *cont, false);
                scene->addActor(*areaCont);
                m_sysManager->reg(*areaCont);
            }
            else if (lootComp)
            {
                areaCont->getContainer().takeFrom(lootComp->get());
            }
            iter = m_registered.erase(iter);
            m_sysManager->unreg(actor->getID());
            m_sceneSystem->getScene()->delActor(*actor);
        }
        else ++iter;
    }
}

void LootGSystem::clean()
{
    m_registered.clear();
}
