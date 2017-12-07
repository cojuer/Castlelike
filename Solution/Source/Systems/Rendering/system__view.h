#pragma once

#include <map>

#include "camera.h"
#include "system.h"

class RenderSubsystem;
class SceneManager;
class SystemManager;

class ViewSystem : public System
{
public:
    ViewSystem() = default;

    bool init(RenderSubsystem& rendSubsys,
              ResourceManager& resManager,
              SystemManager& sysManager, 
              SceneManager& sceneManager);

    bool reg(Actor& actor) override;
    void unreg(ActorID id) override;

    void update() override;

    const Camera& getCamera() const;

private:
    Camera*                   m_camera;
    RenderSubsystem*          m_rendSubsystem;
    ResourceManager*          m_resManager;
    SceneManager*             m_sceneManager;
    SystemManager*            m_sysManager;
    std::map<ActorID, Actor*> m_registered;
};