#pragma once

#include "json_serializable.h"

#include "actor.h"
#include "scene.h"

class Scene;
class ResourceSystem;

using SceneID = std::string;

class SceneSystem final : public JSONSerializable
{
public:
    SceneSystem() = default;
    bool init(ResourceSystem& resSystem);

    void load(SceneID id);
    void clean();
    void load(const Json& node, ResourceSystem& resSystem) override;
    Json save() const override;

    Scene* getScene() const;

    bool loadState(Json& state, ResourceSystem& resSystem);
    Json getState() const;

    std::string getStringID() const override;
    static const std::string stringID;

private:
    // TEST
    void loadTestScene1();
    Coord findEmpty() const;

private:
    ResourceSystem* m_resSystem;
    Scene*          m_scene;
};