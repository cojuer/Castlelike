#pragma once

#include "actor.h"
#include "scene.h"

class Scene;
class SystemManager;
class ResourceManager;

using SceneID = std::string;

class SceneManager
{
public:
    SceneManager() = default;
    bool init(SystemManager& sysManager, ResourceManager& resManager);

    void load(SceneID id);
    void unload(SceneID id);
    void save(SceneID id);

    Scene* getScene() const;

    bool loadState(Json& state, ResourceManager& resManager);
    Json getState() const;

private:
    // TEST
    void loadTestScene1();
    Coord findEmpty() const;

private:
    SystemManager*   m_sysManager;
    ResourceManager* m_resManager;
    Scene*           m_scene;
};