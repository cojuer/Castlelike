#include "action__mighty_blow.h"

#include "rng.h"

MightyBlowAction::MightyBlowAction(ActionArgs&& args) :
    AttackAction(std::move(args))
{}

void MightyBlowAction::act()
{
    auto& attacker = *get<Actor*>(m_args, ActArgType::user);

    RNG rng;
    for (auto victim : getVictims())
    {
        auto hitType = chooseHitType(attacker, *victim, rng);
        auto damage = countDamage(hitType, attacker, *victim);
        dealDamage(*victim, damage);
        updateExperience(attacker, *victim);
        updateJournal(attacker, *victim, hitType, damage);
    }
}