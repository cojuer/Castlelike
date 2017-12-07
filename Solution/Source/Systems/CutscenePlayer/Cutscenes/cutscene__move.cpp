#include "cutscene__move.h"

#include "cutscene_element__move.h"

MoveCutscene::MoveCutscene(Actor& actor, Vec2i tileShift, Duration duration)
{
    m_duration = duration;

    auto elem = new MoveCutsceneElem();
    elem->init(actor, tileShift, duration);
    m_fragments.emplace_back(elem);
}