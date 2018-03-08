#include "app_state__loading.h"

#include "subsystem__event.h"
#include "subsystem__input.h"
#include "subsystem__render.h"
#include "subsystem__rng.h"
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
#include "handler_registration.h"

LoadingAppState LoadingAppState::loadState;

void LoadingAppState::init(App& app)
{
    m_initialized = true;
    m_app = &app;

    EventSubsystem::AddHandler<LoadEvent>(*this);
    
    m_app->m_actorRegistrar.reset(new ActorRegistrar());
    m_app->m_controlSystem.reset(new ControlGSystem());
    m_app->m_lootSystem.reset(new LootGSystem());
    m_app->m_statsSystem.reset(new StatsGSystem());
    m_app->m_sheduleSystem.reset(new SheduleSystem());
    m_app->m_viewSystem.reset(new ViewSystem());

    m_app->m_resSystem->initGame();
    m_app->m_sceneSystem->init(*m_app->m_resSystem);
    m_app->m_sheduleSystem->init();
    m_app->m_viewSystem->init(*m_app->m_rendSubsystem,
                              *m_app->m_resSystem,
                              *m_app->m_sceneSystem);
    m_app->m_controlSystem->init(*m_app->m_inputSubsystem,
                                  *m_app->m_sceneSystem);
    m_app->m_lootSystem->init(*m_app->m_actorRegistrar, 
                               *m_app->m_sceneSystem);
    m_app->m_statsSystem->init();
    
    m_app->m_saveSystem->regSerializable(*m_app->m_rngHolder);
    m_app->m_saveSystem->regSerializable(IDManager::instance());
    m_app->m_saveSystem->regSerializable(*m_app->m_sceneSystem);

    m_app->m_actorRegistrar->addActorHolder(*m_app->m_controlSystem);
    m_app->m_actorRegistrar->addActorHolder(*m_app->m_lootSystem);
    m_app->m_actorRegistrar->addActorHolder(*m_app->m_statsSystem);
    m_app->m_actorRegistrar->addActorHolder(*m_app->m_viewSystem);
}

void LoadingAppState::clean()
{
}

void LoadingAppState::start()
{
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
        m_app->m_sceneSystem->generate();
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

    m_app->changeState(*GameAppState::instance());
}

void LoadingAppState::pause()
{}

void LoadingAppState::resume()
{}

void LoadingAppState::handle()
{
    m_app->m_inputSubsystem->update();
}

void LoadingAppState::update()
{}

void LoadingAppState::render()
{
    m_app->m_rendSubsystem->clear();
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
