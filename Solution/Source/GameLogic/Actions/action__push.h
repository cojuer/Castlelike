#pragma once

#include "action_args.h"
#include "action_interface.h"

#include "vec2.h"

class Actor;
class Scene;

class PushAction final : public ActionInterface
{
public:
    PushAction(ActionArgs&& args = {});

    void act() override;

    void setArg(std::string argType, std::any arg) override;

    std::vector<std::string> getRequiredArgTypes() const override;

    bool canAct() const override;

private:
    std::vector<Actor*> getVictims(Scene& scene, Coord coord) const;
    void pushActorOff(Actor& actor, int weight, Coord weightCoord, Scene& scene);

private:
    ActionArgs  m_args;
};