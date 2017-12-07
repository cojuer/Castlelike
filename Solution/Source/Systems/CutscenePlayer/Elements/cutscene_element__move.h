#pragma once

#include "cutscene_element.h"

#include "vec2.h"
#include "framed_transform.h"

class Actor;

class MoveCutsceneElem : public CutsceneElem
{
public:
    MoveCutsceneElem();

    bool init(Actor& actor, Coord tileDst, Duration duration);

    void onStart() override;
    void update(TimePoint now) override;
    void onFinish() override;

private:
    Actor*          m_actor;
    FramedTransform m_transform;
};
