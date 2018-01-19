#include "cutscene_element__attack.h"

#include "actor.h"

#include "component__transform.h"

AttackCutsceneElem::AttackCutsceneElem() = default;

bool AttackCutsceneElem::init(Actor& actor, Coord destination, Duration duration)
{
    m_actor = &actor;
    // FIXME: use tile_x and tile_y
    auto pixelDst = Vec2i{ destination.x * 24, destination.y * 24 };
    std::map<TimePoint, Transform> timeline = {
        { TimePoint(TimeUnit::s(0)),{ { 0, 0 }, 0, 0 } },
        { TimePoint(duration / 2),{ pixelDst , 0, 0 } },
        { TimePoint(duration),{ { 0, 0 }, 0, 0 } }
    };
    m_transform = FramedTransform{ TimePoint(), duration, std::move(timeline) };
    m_duration = duration;
    return true;
}

void AttackCutsceneElem::onStart()
{
    m_started = true;
}

void AttackCutsceneElem::update(TimePoint now)
{
    m_actor->getComponent<TransformComponent>()->set(m_transform.getTransform(now));
}

void AttackCutsceneElem::onFinish()
{
    m_actor->getComponent<TransformComponent>()->set(Transform());
    m_finished = true;
}