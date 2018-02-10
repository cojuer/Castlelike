#pragma once

#include <map>

#include "camera.h"
#include "actor_holder.h"

class RenderSubsystem;
class SceneSystem;
class ActorRegistrar;

class ViewSystem : public ActorHolder
{
public:
    ViewSystem() = default;

    bool init(RenderSubsystem& rendSubsys,
              ResourceSystem& resSystem,
              SceneSystem& sceneSystem);

    bool reg(Actor& actor) override;
    void unreg(ActorID id) override;

    void render();
    void clean();

    const Camera& getCamera() const;

private:
    RenderSubsystem*          m_rendSubsystem { nullptr };
    ResourceSystem*           m_resSystem { nullptr };
    SceneSystem*              m_sceneSystem { nullptr };
    
    std::unique_ptr<Camera>   m_camera { nullptr };
    std::map<ActorID, Actor*> m_registered;
};