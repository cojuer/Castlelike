#include "action_utils.h"

#include <algorithm>

#include "modifiers.h"
#include "components.h"

#include "rng.h"
#include "vec2.h"
#include "event__journal.h"
#include "subsystem__event.h"

namespace attack
{

HitType getHitType(RNG& rng, int offRating, int defRating)
{
    // FIXME: use consts, no magic numbers
    // TODO: normal hit chance does not change before (0, 0, 40, 40, 20) or (20, 40, 40, 0, 0) 
    double chanceToFail = std::min(std::max(10.0 + (defRating - offRating) * 0.1, 0.0), 20.0);
    double chanceToHitWeak = std::min(std::max(20.0 + (defRating - offRating) * 0.2, 0.0), 40.0);
    double chanceToHitNorm = 40.0;
    double chanceToHitHard = std::min(std::max(20.0 + (offRating - defRating) * 0.2, 0.0), 40.0);
    double chanceToHitCrit = std::min(std::max(10.0 + (offRating - defRating) * 0.1, 0.0), 20.0);
    // FIXME: use eps
    if (100 < defRating - offRating && defRating - offRating <= 233)
    {
        chanceToHitNorm = 40.0 + (100 + offRating - defRating) * 0.3;
        chanceToHitWeak = 40.0 + (defRating - offRating - 100) * 0.2;
        chanceToFail = 20.0 + (defRating - offRating - 100) * 0.1;
    }
    if (233 < defRating - offRating)
    {
        chanceToHitNorm = 0.01;
        chanceToHitWeak = std::max(66.6 + (100 + offRating - defRating) * 0.1, 0.0);
        chanceToFail = 33.3 + (defRating - offRating - 100) * 0.1;
    }
    if (100 < offRating - defRating && offRating - defRating <= 233)
    {
        chanceToHitNorm = 40.0 + (100 + defRating - offRating) * 0.3;
        chanceToHitHard = 40.0 + (offRating - defRating - 100) * 0.2;
        chanceToHitCrit = 20.0 + (offRating - defRating - 100) * 0.1;
    }
    if (233 < offRating - defRating)
    {
        chanceToHitNorm = 0.01;
        chanceToHitHard = std::max(66.6 + (100 + defRating - offRating) * 0.1, 0.0);
        chanceToHitCrit = 33.3 + (offRating - defRating - 100) * 0.1;
    }

    auto hitRandom = rng.get();
    auto hitType = HitType::FAIL;
    Vec2d failRange{ 0.0, chanceToFail };
    Vec2d weakRange{ failRange.y, failRange.y + chanceToHitWeak };
    Vec2d normRange{ weakRange.y, weakRange.y + chanceToHitNorm };
    Vec2d hardRange{ normRange.y, normRange.y + chanceToHitHard };
    Vec2d critRange{ hardRange.y, 100.0 };

    if (failRange.x != failRange.y && failRange.x <= hitRandom && hitRandom <= failRange.y) hitType = HitType::FAIL;
    if (weakRange.x != weakRange.y && weakRange.x <= hitRandom && hitRandom <= weakRange.y) hitType = HitType::WEAK;
    if (normRange.x != normRange.y && normRange.x <= hitRandom && hitRandom <= normRange.y) hitType = HitType::NORM;
    if (hardRange.x != hardRange.y && hardRange.x <= hitRandom && hitRandom <= hardRange.y) hitType = HitType::HARD;
    if (critRange.x != critRange.y && critRange.x <= hitRandom && hitRandom <= critRange.y) hitType = HitType::CRIT;
    return hitType;
}

int getDamage(const Modifiers& attMdfrs, const Modifiers& vicMdfrs, HitType hitType)
{
    int damage = 0;
    if (hitType != HitType::FAIL)
    {
        auto attDamage = attMdfrs.weak_at(Dmg("dmg_ph"));
        if (hitType == HitType::WEAK)
        {
            attDamage /= 2;
        }

        auto vicArmor = vicMdfrs.weak_at(Arm("arm_ph"));
        if (hitType == HitType::HARD)
        {
            vicArmor /= 2;
        }
        else if (hitType == HitType::CRIT)
        {
            vicArmor = 0;
        }
        damage = std::max(attDamage - vicArmor, 0);
    }
    return damage;
}

void updateExperience(Actor& attacker, Actor& victim)
{
    auto attXpComponent = attacker.getComponent<ExperienceInterfaceComponent>();
    auto vicXpComponent = attacker.getComponent<ExperienceInterfaceComponent>();
    if (attXpComponent && vicXpComponent)
    {
        attXpComponent->addXP(vicXpComponent->getLevel() * 5);
        attacker.getComponent<ExperienceInterfaceComponent>()->updateLvl();
    }
}

void updateJournal(const Actor& attacker, const Actor& victim, HitType hitType, int damage)
{
    if (hitType != HitType::FAIL)
    {
        std::string strHitTypeId;
        switch (hitType)
        {
        case HitType::WEAK: strHitTypeId = "hit_weak"; break;
        case HitType::NORM: strHitTypeId = "hit_norm"; break;
        case HitType::HARD: strHitTypeId = "hit_hard"; break;
        case HitType::CRIT: strHitTypeId = "hit_crit"; break;
        default: strHitTypeId = "hit_?";
        }
        auto vecInit = { attacker.getRes() + "_name", victim.getRes() + "_name", strHitTypeId, std::to_string(damage) };
        JournalEvent ev = { std::string("jrn_attack"), vecInit };
        EventSubsystem::FireEvent(ev);
    }
    else
    {
        auto vecInit = { attacker.getRes(), victim.getRes() };
        JournalEvent ev = { std::string("jrn_attack_block"), vecInit };
        EventSubsystem::FireEvent(ev);
    }
}

}
