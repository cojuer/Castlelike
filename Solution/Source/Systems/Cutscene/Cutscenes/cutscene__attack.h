#pragma once

#include "cutscene.h"

#include "cutscene_element__attack.h"

class AttackCutscene : public Cutscene
{
public:
    AttackCutscene(Actor& actor, Vec2i tileShift, Duration duration);
};
