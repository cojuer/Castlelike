#pragma once

#include <map>

#include "actor_holder.h"

class ActorRegistrar;
class SceneSystem;

class LootGSystem : public ActorHolder
{
public:
    LootGSystem() = default;

    bool init(ActorRegistrar& actorRegistrar, SceneSystem& sceneSystem);

    bool reg(Actor& actor) override;
    void unreg(ActorID id) override;

    void update();
    void clean();

private:
    ActorRegistrar*           m_actorRegistrar{ nullptr };
    SceneSystem*              m_sceneSystem { nullptr };
    std::map<ActorID, Actor*> m_registered;
};