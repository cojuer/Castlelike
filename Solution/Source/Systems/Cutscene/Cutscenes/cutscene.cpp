#include "cutscene.h"

Cutscene::Cutscene() :
    m_started(false),
    m_finished(false),
    m_duration(TimeUnit::s(0))
{}

Cutscene::Cutscene(ElemVec&& fragments, Duration duration) :
    m_fragments(std::move(fragments)),
    m_started(false),
    m_finished(false),
    m_duration(duration)
{}

Cutscene::ElemVec& Cutscene::getFragments()
{
    return m_fragments;
}

void Cutscene::start(TimePoint time)
{
    m_start = time;
    m_started = true;
}

void Cutscene::finish()
{
    m_finished = true;
}

TimePoint Cutscene::getStart() const
{
    return m_start;
}

Duration Cutscene::getDuration() const
{
    return m_duration;
}

bool Cutscene::isStarted() const
{
    return m_started;
}

bool Cutscene::isFinished() const
{
    return m_finished;
}
