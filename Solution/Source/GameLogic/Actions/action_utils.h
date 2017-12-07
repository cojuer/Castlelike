#pragma once

#include <string>

class Actor;
class Modifiers;
class RNG;

enum class HitType { FAIL, WEAK, NORM, HARD, CRIT };

namespace attack
{
    HitType getHitType(RNG& rng, int offRating, int defRating);
    int getDamage(const Modifiers& attMdfrs, const Modifiers& vicModifiers, HitType hitType);
    void updateExperience(Actor& attacker, Actor& victim);
    void updateJournal(const Actor& attacker, const Actor& victim, HitType hitType, int damage);
}