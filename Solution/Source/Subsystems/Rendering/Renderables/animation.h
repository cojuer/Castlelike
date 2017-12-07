#pragma once

#include "renderable.h"
#include "framed_transform.h"

class Animation : public Renderable
{
public:
    using TimeLine  = std::map<TimePoint, ATexture*>;

    Animation(TimePoint start, Duration duration, TimeLine&& timeline, bool looped = false);

    Renderable* clone() const override;

    ATexture* getTexture() override;
    const ATexture* getTexture() const override;
    const ATexture* getTexture(TimePoint timePoint) const;

    bool isLooped() const;

private:
    mutable TimePoint m_start;
    Duration  m_duration;
    TimeLine  m_timeline;
    bool      m_looped;
};
