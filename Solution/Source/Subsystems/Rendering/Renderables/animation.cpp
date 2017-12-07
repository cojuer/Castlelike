#include "animation.h"

#include "global_time.h"

Animation::Animation(TimePoint start, 
                     Duration duration,
                     TimeLine&& timeline,
                     bool looped) :
    m_start(start),
    m_duration(duration),
    m_timeline(std::move(timeline)),
    m_looped(looped)
{}

Renderable* Animation::clone() const
{
    return new Animation(*this);
}

bool Animation::isLooped() const
{
    return m_looped;
}

ATexture* Animation::getTexture()
{
    auto now = TimePoint{ GlobalTime::instance().getTicks() };
    if (m_timeline.size() == 0)
    {
        return nullptr;
    }
    if (now - m_start > m_duration && !m_looped)
    {
        return m_timeline.rbegin()->second;
    }
    if (now - m_start > m_duration)
    {
        auto times = (now - m_start) / m_duration;
        m_start += times * m_duration;
    }
    TimePoint relativeNow{ now - m_start };
    auto resultIter = std::prev(m_timeline.lower_bound(relativeNow));
    return resultIter->second;
}

const ATexture* Animation::getTexture() const
{
    auto now = TimePoint{ GlobalTime::instance().getTicks() };
    if (m_timeline.size() == 0)
    {
        return nullptr;
    }
    if (now - m_start > m_duration && !m_looped)
    {
        return m_timeline.rbegin()->second;
    }
    if (now - m_start > m_duration)
    {
        auto times = (now - m_start) / m_duration;
        m_start += times * m_duration;
    }
    TimePoint relativeNow{ now - m_start };
    auto resultIter = std::prev(m_timeline.lower_bound(relativeNow));
    return resultIter->second;
}

const ATexture* Animation::getTexture(TimePoint timePoint) const
{
    if (m_timeline.size() == 0)
    {
        return nullptr;
    }
    if (timePoint - m_start > m_duration && !m_looped)
    {
        return m_timeline.rbegin()->second;
    }
    if (timePoint - m_start > m_duration)
    {
        auto times = (timePoint - m_start) / m_duration;
        m_start += times * m_duration;
    }
    TimePoint animTimePoint{ timePoint - m_start };
    auto resultIter = std::prev(m_timeline.lower_bound(animTimePoint));
    return resultIter->second;
}
