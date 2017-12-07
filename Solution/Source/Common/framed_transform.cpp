#include "framed_transform.h"

#include <iostream>
#include <cassert>

FramedTransform::FramedTransform() = default;

FramedTransform::FramedTransform(TimePoint start, Duration duration, Timeline&& timeline, bool looped) :
    m_start(start),
    m_duration(duration),
    m_timeline(std::move(timeline)),
    m_looped(looped)
{}

void FramedTransform::setStart(const TimePoint start) const
{
    m_start = start;
}

TimePoint FramedTransform::getStart() const
{
    return m_start;
}

Duration FramedTransform::getDuration() const
{
    return m_duration;
}

Transform FramedTransform::getTransform(const TimePoint timePoint) const
{
    assert(m_timeline.size() != 0 && "empty transform timeline");
    if (timePoint - m_start >= m_duration && !m_looped)
    {
        return m_timeline.rbegin()->second;
    }
    if (timePoint - m_start >= m_duration)
    {
        const auto times = (timePoint - m_start) / m_duration;
        m_start += times * m_duration;
    }
    const TimePoint relativeNow{ timePoint - m_start };
    const auto geqIter = m_timeline.lower_bound(relativeNow);
    const TimePoint afterNow = geqIter->first;
    const TimePoint beforeNow = (geqIter != m_timeline.begin()) ? std::prev(geqIter)->first : afterNow;
    auto timeBetweenFrames = afterNow - beforeNow;
    if (timeBetweenFrames == TimeUnit::ms(0))
    {
        timeBetweenFrames = TimeUnit::ms(1);
    }
    const float beforeContrib = 1. * (relativeNow - beforeNow).count() / timeBetweenFrames.count();
    const float afterContrib = 1. *(afterNow - relativeNow).count() / timeBetweenFrames.count();

    const Transform transform{
        { static_cast<int>(m_timeline.at(beforeNow).m_shift.x * afterContrib + 
                           m_timeline.at(afterNow).m_shift.x * beforeContrib),
          static_cast<int>(m_timeline.at(beforeNow).m_shift.y * afterContrib + 
                           m_timeline.at(afterNow).m_shift.y * beforeContrib) },
        0,
        0
    };
    return transform;
}

const FramedTransform::Timeline& FramedTransform::getTimeline() const
{
    return m_timeline;
}
