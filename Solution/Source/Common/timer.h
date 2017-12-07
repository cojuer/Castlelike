#pragma once

#include "time_aliases.h"

class Timer
{
public:
    Timer();

    void start();
    void stop();
    void pause();
    void unpause();

    Duration getTicks() const;

    bool isStarted() const;
    bool isPaused() const;

private:
    TimePoint m_start;
    Duration  m_pauseDuration;

    bool      m_paused;
    bool      m_started;
};
