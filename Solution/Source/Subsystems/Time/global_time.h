#pragma once

#include "time_aliases.h"
#include "timer.h"

class GlobalTime final
{
public:
    static GlobalTime& instance();

    GlobalTime(GlobalTime const&) = delete;
    GlobalTime(GlobalTime&&) = delete; 
    GlobalTime& operator=(GlobalTime const&) = delete;
    GlobalTime& operator=(GlobalTime &&) = delete;

    void start();
    void stop(); 
    void pause();
    void unpause();

    Duration getTicks() const;

    bool isStarted() const;
    bool isPaused() const;

protected:
    GlobalTime() = default;
    ~GlobalTime() = default;

private:
    Timer m_timer;
};
