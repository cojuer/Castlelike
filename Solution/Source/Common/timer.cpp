#include "timer.h"

Timer::Timer() :
    m_start(Clock::now()),
    m_pauseDuration(0),
    m_paused(false),
    m_started(false)
{};

void Timer::start()
{
    m_started = true;
    m_paused = false;
    m_start = Clock::now();
    m_pauseDuration = Seconds(0);
}

void Timer::stop()
{
    m_started = false;
    m_paused = false;
}

void Timer::pause()
{
    if (m_started && !m_paused)
    {
        m_paused = true;
        m_pauseDuration = Clock::now() - m_start;
    }
}
void Timer::unpause()
{
    if (m_started && m_paused)
    {
        m_paused = false;
        m_start = Clock::now() - m_pauseDuration;
    }
}

Duration Timer::getTicks() const
{
    if (m_started)
    {
        if (m_paused)
        {
            return m_pauseDuration;
        }
        else
        {
            return (Clock::now() - m_start);
        }
    }
    return Seconds(0);
}

bool Timer::isStarted() const
{
    return m_started;
}

bool Timer::isPaused() const
{
    return m_paused;
}
