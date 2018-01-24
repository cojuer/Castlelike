#pragma once

#include <map>

#include "game_system.h"

class SceneSystem;
class GameSystemManager;

class LootGSystem : public GameSystem
{
public:
    LootGSystem() = default;

    bool init(GameSystemManager& sysManager, SceneSystem& sceneSystem);

    bool reg(Actor& actor) override;
    void unreg(ActorID id) override;

    void update() override;
    void clean() override;

private:
    SceneSystem*              m_sceneSystem;
    GameSystemManager*        m_sysManager;
    std::map<ActorID, Actor*> m_registered;
};