#pragma once

#include "actor.h"
#include "scene.h"

class Scene;
class GameSystemManager;
class ResourceSystem;

using SceneID = std::string;

class SceneSystem
{
public:
    SceneSystem() = default;
    bool init(GameSystemManager& sysManager, ResourceSystem& resSystem);

    void load(SceneID id);
    void unload(SceneID id);
    void load(const Json& node, ResourceSystem& resSystem);
    Json save() const;

    Scene* getScene() const;

    bool loadState(Json& state, ResourceSystem& resSystem);
    Json getState() const;

private:
    // TEST
    void loadTestScene1();
    Coord findEmpty() const;

private:
    GameSystemManager*   m_sysManager;
    ResourceSystem* m_resSystem;
    Scene*           m_scene;
};