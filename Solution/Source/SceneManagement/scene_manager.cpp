#include "scene_manager.h"

#include <iostream>

#include "resource_manager.h"

#include "actions.h"
#include "scene.h"
#include "attributes.h"
#include "container.h"
#include "equipment.h"
#include "actor__door.h"
#include "utils.h"
#include "factory__newarea.h"
#include "id_manager.h"

#include "subsystem_io.h"

#include "components.h"

//TEST
#include "factory__actor.h"
#include "dialmanager.h"
#include "action__damage.h"
#include "action__heal.h"

bool SceneManager::init(SystemManager& sysManager, ResourceManager& resManager)
{
    m_sysManager = &sysManager;
    m_resManager = &resManager;
    return true;
}

void SceneManager::load(SceneID id)
{
    loadTestScene1();
}

void SceneManager::unload(SceneID id)
{
    
}

void SceneManager::save(SceneID id)
{
    
}

void SceneManager::loadTestScene1()
{
    std::vector<Actor*> actors;

    auto& idManager = IDManager::instance();
    m_scene = m_resManager->get<Scene>("test");
    
    auto attrs = new Attributes();
    (*attrs)[Attr("str")] = 5;
    (*attrs)[Attr("dex")] = 5;
    (*attrs)[Attr("int")] = 5;
    (*attrs)[Attr("per")] = 5;
    (*attrs)[Attr("chr")] = 5;
    (*attrs)[Attr("vit")] = 5;

    auto hero = new Actor(idManager.getActorID(), "hero");
    hero->addComponent<PlayerComponent>(*new PlayerComponent());
    hero->addComponent<PositionComponent>(*new PositionComponent());
    hero->addComponent<AttrComponent>(*new AttrComponent(*attrs));

    Modifiers mdfrs;
    for (auto& type : Modifiers::types)
    {
        mdfrs[type] = 0;
    }
    hero->addComponent<TransformComponent>(*new TransformComponent());
    hero->addComponent<MdfrComponent>(*new MdfrComponent(mdfrs));
    hero->addComponent<GraphicsInterfaceComponent>(*new GraphicsComponent(10, { "Hero" }));
    hero->addComponent<HealthComponent>(*new HealthComponent(0, 1000, 1000));
    hero->addComponent<StaminaComponent>(*new StaminaComponent(0, 100, 100));
    hero->addComponent<WeightComponent>(*new WeightComponent(1, 1, 1));
    hero->addComponent<ExperienceInterfaceComponent>(*new ExperienceComponent(1, 200));
    hero->addComponent<BagComponent>(*new BagComponent());
    hero->addComponent<EquipmentComponent>(*new EquipmentComponent());
    hero->addComponent<ReactorComponentInterface>(*new ReactorComponent());
    hero->addComponent<CollisionComponent>(*new CollisionComponent());
    hero->addComponent<ActionPtsComponent>(*new ActionPtsComponent());

    hero->getComponent<CollisionComponent>()->set(true);
    hero->getComponent<TransformComponent>()->set({ { 0 ,0 }, 0, 0 });

    auto bagComponent = hero->getComponent<BagComponent>();
    std::vector<std::string> initialItems = {
        "item_golden_sword",
        "item_rusty_sword",
        "item_knife",
        "item_steel_sword",
        "item_hide_bracers"
    };
    for (auto& itemName : initialItems)
    {
        auto item = m_resManager->get<Item>(itemName);
        assert(item);
        bagComponent->add(*item);
    }
    auto& equipment = hero->getComponent<EquipmentComponent>()->get();
    std::vector<std::string> itemsToEquip = {
        "item_mithril_helmet",
        "item_mithril_pants",
        "item_mithril_boots",
        "item_mithril_jacket",
        "item_mithril_spaulders",
        "item_mithril_gloves",
        "item_mithril_bracers"
    };
    for (auto& itemName : itemsToEquip)
    {
        auto item = m_resManager->get<Item>(itemName);
        assert(item);
        equipment.equip(*item);
    }
    
    equipment.equip("rhand", *m_resManager->get<Item>("item_golden_sword"));

    auto reactor = hero->getComponent<ReactorComponent>();
    if (reactor)
    {
        ActionArgs fstinput{ { "user", dcast<Actor*>(hero) },{ "dmg_psn", 20 },{ "dmg_mgc", 1 },{ "duration", 3 } };
        ActionInterface* action = new DamageAction{ std::move(fstinput) };
        auto reaction = Reaction("damage", action);
        reactor->addReaction("move", std::move(reaction));

        ActionArgs sndinput{ { "user", dcast<Actor*>(hero) },{ "power", 1 },{ "duration", 6 } };
        action = new HealAction{ std::move(sndinput) };
        reaction = Reaction("heal", action);
        reactor->addReaction("move", std::move(reaction));
    }
    if (hero->getComponent<MdfrComponent>())
    {
        hero->getComponent<MdfrComponent>()->refresh();
    }
    
    for (auto i = 0; i < 20; ++i)
    {
        auto rat = m_resManager->get<Actor>("npc_rat");
        
        if (rat)
        {
            rat->setCoord(findEmpty());
            if (rat->getComponent<MdfrComponent>())
            {
                rat->getComponent<MdfrComponent>()->refresh();
            }
            m_scene->addActor(*rat);
            actors.push_back(rat);
        }
    }
    std::cout << "actors size: " << actors.size() << std::endl;

    auto heroCoord = findEmpty();
    hero->setCoord(heroCoord);
    m_scene->addActor(*hero);
    auto door = new Door(idManager.getActorID(), { heroCoord.x + 1, heroCoord.y }, "door_normal", true);
    actors.push_back(door);
    m_scene->addActor(*door);
    actors.push_back(hero);
}

Coord SceneManager::findEmpty() const
{
    auto counter = 0;
    while (true)
    {
        int x = rand() % m_scene->getWidth();
        int y = rand() % m_scene->getHeight();
        if (m_scene->getTile({ x, y }) != nullptr &&
            !m_scene->getTile({ x, y })->isCollisive())
        {
            auto collisive = false;
            auto actors = m_scene->getActorsAtCoord({ x, y });
            for (auto actor : actors)
            {
                collisive = collisive || actor->isCollisive();
            }
            if (!collisive)
            {
                return { x, y };
            }
        }
        ++counter;
        // check cycles
        assert(counter < 10000);
    }
}

Scene* SceneManager::getScene() const
{
    return m_scene;
}

bool SceneManager::loadState(Json& state, ResourceManager& resManager)
{
    auto sceneNode = state.at("scene");
    m_scene = new Scene{};
    m_scene->fromJSON(state, *m_resManager);

    // FIXME: test whether scene was loaded
    return true;
}

Json SceneManager::getState() const
{
    return m_scene->toJSON();
}
