#pragma once

#include "actor.h"
#include "cutscene_element.h"

class Cutscene
{
    using ElemVec = std::vector<std::unique_ptr<CutsceneElem>>;

public:
    Cutscene();
    Cutscene(ElemVec&& fragments, Duration duration);

    ElemVec& getFragments();
    void start(TimePoint time);
    void finish();

    TimePoint getStart() const;
    Duration  getDuration() const;

    bool isStarted() const;
    bool isFinished() const;

protected:
    ElemVec m_fragments;
    bool m_started;
    bool m_finished;
    TimePoint m_start;
    Duration  m_duration;
};
