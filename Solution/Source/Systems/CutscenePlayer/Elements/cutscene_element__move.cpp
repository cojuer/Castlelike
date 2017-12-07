#include "cutscene_element__move.h"

#include "actor.h"

#include "component__transform.h"

MoveCutsceneElem::MoveCutsceneElem() = default;

bool MoveCutsceneElem::init(Actor& actor, Coord tileDst, Duration duration)
{
    m_actor = &actor;
    // FIXME: use tile_x and tile_y
    auto pixelDst = Vec2i{ tileDst.x * 64, tileDst.y * 64 };
    std::map<TimePoint, Transform> timeline = {
        { TimePoint(TimeUnit::ms(0)),{ { 0, 0 }, 0, 0 } },
        { TimePoint(duration),{ pixelDst, 0, 0 } },
    };
    m_transform = FramedTransform{ TimePoint(), duration, std::move(timeline) };
    m_duration = duration;
    return true;
}

void MoveCutsceneElem::onStart()
{
    m_started = true;
}

void MoveCutsceneElem::update(TimePoint now)
{
    m_actor->getComponent<TransformComponent>()->set(m_transform.getTransform(now));
}

void MoveCutsceneElem::onFinish()
{
    m_actor->getComponent<TransformComponent>()->set(Transform());
    m_finished = true;
}