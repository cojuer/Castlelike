#pragma once

#include <map>

#include "time_aliases.h"
#include "transform.h"

class FramedTransform
{
public:
    using Timeline = std::map<TimePoint, Transform>;

    FramedTransform();
    FramedTransform(TimePoint start, Duration duration, Timeline&& timeline, bool looped = false);

    void setStart(TimePoint start) const;

    TimePoint getStart() const;
    Duration  getDuration() const;
    Transform getTransform(TimePoint timePoint) const;
    const Timeline& getTimeline() const;

private:
    mutable TimePoint m_start;
    Duration          m_duration;
    Timeline          m_timeline;
    bool              m_looped;
};