#pragma once

#include <map>

#include "camera.h"
#include "game_system.h"

class RenderSubsystem;
class SceneSystem;
class GameSystemManager;

class ViewSystem : public GameSystem
{
public:
    ViewSystem() = default;

    bool init(RenderSubsystem& rendSubsys,
              ResourceSystem& resSystem,
              GameSystemManager& sysManager, 
              SceneSystem& sceneSystem);

    bool reg(Actor& actor) override;
    void unreg(ActorID id) override;

    void update() override;

    const Camera& getCamera() const;

private:
    Camera*                   m_camera;
    RenderSubsystem*          m_rendSubsystem;
    ResourceSystem*          m_resSystem;
    SceneSystem*             m_sceneSystem;
    GameSystemManager*            m_sysManager;
    std::map<ActorID, Actor*> m_registered;
};