#pragma once

#include <queue>
#include <map>

#include "system.h"

#include "event__actor.h"
#include "event_handler.h"

class SystemManager;

class StatsSystem : public System, public EventHandler<ActorEvent>
{
public:
    StatsSystem() = default;

    bool init(SystemManager& sysManager);

    bool reg(Actor& actor) override;
    void unreg(ActorID id) override;

    void update() override;

    void onEvent(ActorEvent& event) override;

private:
    SystemManager*            m_sysManager;
    std::map<ActorID, Actor*> m_registered;
    std::queue<Actor*>        m_updated;
};