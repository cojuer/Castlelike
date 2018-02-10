#pragma once

#include <queue>
#include <map>

#include "actor_holder.h"

#include "event__actor.h"
#include "event_handler.h"

class HandlerRegistration;

class StatsGSystem : public ActorHolder, public EventHandler<ActorEvent>
{
public:
    StatsGSystem();

    ~StatsGSystem();

    bool init();

    bool reg(Actor& actor) override;
    void unreg(ActorID id) override;

    void update();
    void clean();

    void onEvent(ActorEvent& event) override;

private:
    std::map<ActorID, Actor*> m_registered;
    std::queue<Actor*>        m_updated;

    std::unique_ptr<HandlerRegistration> m_reg;
};