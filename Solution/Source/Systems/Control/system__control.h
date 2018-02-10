#pragma once

#include <set>
#include <vector>

#include "actor_holder.h"

class SceneSystem;
class InputSubsystem;
class AIController;
class Controller;
class PlayerController;
class ActorRegistrar;

class ControlGSystem : public ActorHolder
{
public:
    ControlGSystem() = default;

    bool init(InputSubsystem& inputSubsystem, SceneSystem& sceneSystem);

    bool reg(Actor& actor) override;
    void unreg(ActorID id) override;

    void update();
    void clean();

    ActorID getCurrentID();

    AIController*            m_aiController { nullptr };
    PlayerController*        m_plController { nullptr };

private:
    std::vector<std::pair<size_t, Actor*>> m_possessed;
    size_t                   m_current { 0 };
    bool                     m_giveAP { true };
    std::set<ActorID>        m_registered;
    std::vector<Controller*> m_controllers;

};