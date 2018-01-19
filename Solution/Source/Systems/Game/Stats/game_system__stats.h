#pragma once

#include <queue>
#include <map>

#include "game_system.h"

#include "event__actor.h"
#include "event_handler.h"

class GameSystemManager;

class StatsGSystem : public GameSystem, public EventHandler<ActorEvent>
{
public:
    StatsGSystem() = default;

    bool init(GameSystemManager& sysManager);

    bool reg(Actor& actor) override;
    void unreg(ActorID id) override;

    void update() override;

    void onEvent(ActorEvent& event) override;

private:
    GameSystemManager*         m_sysManager;
    std::map<ActorID, Actor*> m_registered;
    std::queue<Actor*>        m_updated;
};