#include "system__loot.h"

#include "scene.h"
#include "container.h"
#include "actor__storage.h"

#include "id_manager.h"
#include "scene_manager.h"
#include "system_manager.h"

#include "component__bag.h"
#include "component__equipment.h"
#include "component__health.h"
#include "component__loot.h"

bool LootSystem::init(SystemManager& sysManager, SceneManager& sceneManager)
{
    m_sceneManager = &sceneManager;
    m_sysManager = &sysManager;
    return true;
}

bool LootSystem::reg(Actor& actor)
{
    auto hpComponent = actor.getComponent<HealthComponent>();
    if (hpComponent)
    {
        m_registered.insert(std::make_pair(actor.getID(), &actor));
        return true;
    }
    return false;
}

void LootSystem::unreg(ActorID id)
{
    m_registered.erase(id);
}

void LootSystem::update()
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
            auto scene = m_sceneManager->getScene();
            auto areaCont = dynamic_cast<StorageActor*>(scene->getActor(coord, "cont"));
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
            m_sceneManager->getScene()->delActor(*actor);
        }
        else ++iter;
    }
}