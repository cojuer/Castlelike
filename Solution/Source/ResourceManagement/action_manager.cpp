#include "action_manager.h"

#include "actions.h"

void ActMgr::init()
{
    data["action_move"]   = createAction<MoveAction>;
    data["action_attack"] = createAction<AttackAction>;
    data["action_damage"] = createAction<DamageAction>;
    data["action_heal"]   = createAction<HealAction>;
    data["action_discard"] = createAction<PushAction>;
    data["action_whirlwind"] = createAction<WhirlwindAction>;
    data["action_swing"] = createAction<SwingAction>;
    data["action_mighty_blow"] = createAction<MightyBlowAction>;
}

ActionArgs ActMgr::getNeeded(std::string name) const
{
    return input.at(name);
}

ActionInterface* ActMgr::getAction(std::string name, ActionArgs&& args) const
{
    auto create = data.at(name);
    return create(std::move(args));
}