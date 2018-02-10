#pragma once

#include "cutscene_element.h"

#include "vec2.h"
#include "framed_transform.h"

class Actor;

class AttackCutsceneElem : public CutsceneElem
{
public:
    AttackCutsceneElem();

    bool init(Actor& actor, Coord destination, Duration duration);

    void onStart() override;
    void update(TimePoint now) override;
    void onFinish() override;

private:
    Actor*          m_actor { nullptr };
    FramedTransform m_transform;
};
