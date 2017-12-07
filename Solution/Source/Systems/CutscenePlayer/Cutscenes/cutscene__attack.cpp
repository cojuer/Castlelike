#include "cutscene__attack.h"

#include "cutscene_element__attack.h"

AttackCutscene::AttackCutscene(Actor& actor, Vec2i tileShift, Duration duration)
{
    m_duration = duration;

    auto elem = new AttackCutsceneElem();
    elem->init(actor, tileShift, duration);
    m_fragments.emplace_back(elem);
}