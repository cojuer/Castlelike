#pragma once

#include "time_aliases.h"

class CutsceneElem
{
public:
    virtual ~CutsceneElem();

    virtual void onStart() = 0;
    virtual void update(TimePoint now) = 0;
    virtual void onFinish() = 0;

    virtual TimePoint getStart() const;
    virtual Duration  getDuration() const;

    bool hasStarted() const;
    bool hasFinished() const;

protected:
    bool      m_started{ false };
    bool      m_finished{ false };
    TimePoint m_start;
    Duration  m_duration;
};