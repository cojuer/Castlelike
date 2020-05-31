#include "app_state__loading.h"

#include <filesystem>

#include "subsystem__event.h"
#include "subsystem__input.h"
#include "subsystem__render.h"
#include "subsystem__rng.h"
#include "subsystem_io.h"
#include "system__resource.h"
#include "system__save.h"
#include "system__scene.h"
#include "system__shedule.h"
#include "system__view.h"
#include "system__actor_registrar.h"
#include "system__control.h"

#include "app_state__game.h"
#include "system__actor_id.h"
#include "game_gui.h"
#include "widget.h"
#include "handler_registration.h"
#include "listener__control.h"
#include "json_aliases.h"

namespace fs = std::filesystem;

LoadingAppState LoadingAppState::loadState;

void LoadingAppState::init(App& app)
{
    m_initialized = true;
    m_app = &app;

    EventSubsystem::AddHandler<LoadEvent>(*this);
    
    m_app->m_actorRegistrar.reset(new ActorRegistrar());
    m_app->m_controlGSystem.reset(new ControlGSystem());
    m_app->m_lootGSystem.reset(new LootGSystem());
    m_app->m_statsGSystem.reset(new StatsGSystem());
    m_app->m_sheduleSystem.reset(new SheduleSystem());
    m_app->m_viewSystem.reset(new ViewSystem());

    m_app->m_resSystem->initGame();
    m_app->m_sceneSystem->init(*m_app->m_resSystem);
    m_app->m_sheduleSystem->init();
    m_app->m_viewSystem->init(*m_app->m_rendSubsystem,
                              *m_app->m_resSystem,
                              *m_app->m_sceneSystem);
    m_app->m_controlGSystem->init(*m_app->m_inputSubsystem,
                                  *m_app->m_sceneSystem);

    auto listener = new ControlListener(*m_app->m_controlGSystem->m_plController);
    EventSubsystem::AddHandler(*listener);

    m_app->m_lootGSystem->init(*m_app->m_actorRegistrar, 
                               *m_app->m_sceneSystem);
    m_app->m_statsGSystem->init();
    
    m_app->m_saveSystem->regSerializable(*m_app->m_rngHolder);
    m_app->m_saveSystem->regSerializable(IDManager::instance());
    m_app->m_saveSystem->regSerializable(*m_app->m_sceneSystem);

    m_app->m_actorRegistrar->addActorHolder(*m_app->m_controlGSystem);
    m_app->m_actorRegistrar->addActorHolder(*m_app->m_lootGSystem);
    m_app->m_actorRegistrar->addActorHolder(*m_app->m_viewSystem);
    m_app->m_actorRegistrar->addActorHolder(*m_app->m_statsGSystem);

    auto fullScreenRect = SDL_Rect{
        0, 0,
        m_app->m_opts.get<int>(OptType::WIDTH), 
        m_app->m_opts.get<int>(OptType::HEIGHT) 
    };
    m_loadingScreen.reset(
        new gui::Widget(
            "loading_screen", nullptr, fullScreenRect, true,
            m_app->m_resSystem->get<Renderable>("loading_screen")
        )
    );
}

void LoadingAppState::clean()
{
}

void LoadingAppState::start()
{
    /* hack to enable control on start, better way is to add start/stop to every game system */
    m_app->m_controlGSystem->m_plController->set_to_control(true);

    if (m_app->m_loadSave)
    {
        if (m_app->m_loadLast)
        {
            m_app->m_saveSystem->loadLast(*m_app->m_resSystem);
        }
        else
        {
            m_app->m_saveSystem->load(m_profile, m_save, *m_app->m_resSystem);
        }
    }
    else
    {
        auto demoPath = fs::path("Assets") / "Databases" / "sceneDB.json";
        Json sceneDBnode;
        *IOSubsystem::getInStream(demoPath) >> sceneDBnode;
        m_app->m_saveSystem->loadJson(sceneDBnode["demo"], *m_app->m_resSystem);
    }

    for (auto& [id, actor] : m_app->m_sceneSystem->getScene()->getIDToActorMap())
    {
        m_app->m_actorRegistrar->reg(*actor);
    }

    m_app->m_gameGUI.reset(new gui::GameGUI());
    m_app->m_gameGUI->init(m_app->m_opts,
                           *m_app->m_rendSubsystem,
                           *m_app->m_viewSystem,
                           *m_app->m_journalSystem,
                           *m_app->m_sceneSystem,
                           *m_app->m_resSystem);
}

void LoadingAppState::pause()
{}

void LoadingAppState::resume()
{}

void LoadingAppState::handle()
{
    m_app->m_inputSubsystem->update();

    for (auto event : m_app->m_inputSubsystem->getEvents())
    {
        if (event.type == SDL_KEYDOWN || event.type == SDL_MOUSEBUTTONUP) {
            m_app->changeState(*GameAppState::instance());
        }
    }
}

void LoadingAppState::update()
{}

void LoadingAppState::render()
{
    m_app->m_rendSubsystem->clear();
    m_loadingScreen->render(*m_app->m_rendSubsystem, *m_app->m_resSystem);
    m_app->m_rendSubsystem->renderPresent();
}

LoadingAppState* LoadingAppState::instance()
{
    return &loadState;
}

void LoadingAppState::onEvent(LoadEvent& event)
{
    m_profile = event.m_profile;
    m_save = event.m_save;
}
