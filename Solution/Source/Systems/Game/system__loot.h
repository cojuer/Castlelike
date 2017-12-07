#pragma once

#include <map>

#include "system.h"

class SceneManager;
class SystemManager;

class LootSystem : public System
{
public:
    LootSystem() = default;

    bool init(SystemManager& sysManager, SceneManager& sceneManager);

    bool reg(Actor& actor) override;
    void unreg(ActorID id) override;

    void update() override;

private:
    SceneManager*             m_sceneManager;
    SystemManager*            m_sysManager;
    std::map<ActorID, Actor*> m_registered;
};