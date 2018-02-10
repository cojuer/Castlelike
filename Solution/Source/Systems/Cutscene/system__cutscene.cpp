#include "system__cutscene.h"

#include "cutscene.h"
#include "cutscene_element.h"
#include "global_time.h"

void CutsceneSystem::startCutscene(Cutscene& cutscene)
{
    m_currentCutscene = &cutscene;
    m_currentCutscene->start(TimePoint{ GlobalTime::instance().getTicks() });
}

void CutsceneSystem::updateCutscene()
{
    const auto cutsceneTime = TimePoint{ TimePoint{ GlobalTime::instance().getTicks() } - m_currentCutscene->getStart() };
    for (auto& fragment : m_currentCutscene->getFragments())
    {
        if (cutsceneTime >= fragment->getStart() && 
            cutsceneTime <= fragment->getStart() + fragment->getDuration())
        {
            if (!fragment->hasStarted())
            {
                fragment->onStart();
            }
            fragment->update(cutsceneTime);
        }
        if (cutsceneTime >= fragment->getStart() + fragment->getDuration())
        {
            if (!fragment->hasFinished())
            {
                fragment->onFinish();
            }
        }
    }
    if (cutsceneTime > TimePoint{ m_currentCutscene->getDuration() })
    {
        finishCutscene();
    }
}

void CutsceneSystem::finishCutscene()
{
    for (auto& fragment : m_currentCutscene->getFragments())
    {
        if (!fragment->hasFinished())
        {
            fragment->onFinish();
        }
    }
    delete(m_currentCutscene);
    m_currentCutscene = nullptr;
}

bool CutsceneSystem::onCutscene() const
{
    return m_currentCutscene && 
           m_currentCutscene->isStarted() && 
           !m_currentCutscene->isFinished();
}
