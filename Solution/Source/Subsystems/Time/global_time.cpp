#include "global_time.h"

GlobalTime& GlobalTime::instance()
{
    static GlobalTime instance;
    return instance;
}

void GlobalTime::start()
{
    m_timer.start();
}

void GlobalTime::stop()
{
    m_timer.stop();
}

void GlobalTime::pause()
{
    m_timer.pause();
}
void GlobalTime::unpause()
{
    m_timer.unpause();
}

Duration GlobalTime::getTicks() const
{
    return m_timer.getTicks();
}

bool GlobalTime::isStarted() const
{
    return m_timer.isStarted();
}

bool GlobalTime::isPaused() const
{
    return m_timer.isPaused();
}
