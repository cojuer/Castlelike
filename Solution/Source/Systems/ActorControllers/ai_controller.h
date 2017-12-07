#pragma once

#include <map>

#include "id_manager.h"
#include "controller.h"

class SceneManager;
class SystemManager;

class AIController : public Controller
{
public:
    AIController() = default;

    bool init(SceneManager& sceneManager, SystemManager& sysManager);

    bool possess(Actor& actor) override;
    bool control(Actor& actor) override;

private:
    SceneManager*             m_sceneManager;
    SystemManager*            m_sysManager;
    std::map<ActorID, Actor*> m_registered;
};