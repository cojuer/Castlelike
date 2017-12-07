#include "cutscene_element.h"

CutsceneElem::~CutsceneElem() = default;

TimePoint CutsceneElem::getStart() const
{
    return m_start;
}

Duration CutsceneElem::getDuration() const
{
    return m_duration;
}

bool CutsceneElem::hasStarted() const
{
    return m_started;
}

bool CutsceneElem::hasFinished() const
{
    return m_finished;
}
