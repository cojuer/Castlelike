#pragma once

#include "cutscene.h"

class MoveCutscene : public Cutscene
{
public:
    MoveCutscene(Actor& actor, Vec2i tileShift, Duration duration);
};
