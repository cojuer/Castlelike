#include "action__attack.h"

#include "scene.h"
#include "vec2.h"
#include "rng.h"

#include "component__attr.h"
#include "component__mdfr.h"
#include "component__health.h"
#include "event_bus.h"

#include "action_utils.h"
#include "component__action_pts.h"

AttackAction::AttackAction(ActionArgs&& args) : 
    m_args(std::move(args))
{}

void AttackAction::act()
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
    
    wasteAP(attacker);
}

void AttackAction::setArg(std::string argType, std::any arg)
{
    m_args[argType] = arg;
}

std::vector<std::string> AttackAction::getRequiredArgTypes() const
{
    std::vector<std::string> allArgTypesNeeded = {
        ActArgType::user,
        ActArgType::scene,
        ActArgType::coord
    };
    std::vector<std::string> argTypesNeeded;
    for (auto& type : allArgTypesNeeded)
    {
        if (m_args.find(type) == m_args.end())
        {
            argTypesNeeded.push_back(type);
        }
    }
    return argTypesNeeded;
}

bool AttackAction::canAct() const
{
    if (getRequiredArgTypes().size() == 0)
    {
        return true;
    }
    return false;
}

std::vector<Actor*> AttackAction::getVictims() const
{
    auto& scene = *get<Scene*>(m_args, ActArgType::scene);
    auto& coord = *get<Coord*>(m_args, ActArgType::coord);
    std::vector<Actor*> victims;
    for (auto& actor : scene.getActorsAtCoord(coord))
    {
        auto hpComp = actor->getComponent<HealthComponent>();
        bool actorOk = hpComp;
        if (actorOk)
        {
            victims.push_back(actor);
        }
    }
    return victims;
}

HitType AttackAction::chooseHitType(const Actor& attacker, const Actor& victim, RNG& rng) const
{
    auto attMdfrComp = attacker.getComponent<MdfrComponent>();
    auto attOffRating = attMdfrComp->get().weak_at("off_rating");

    auto vicMdfrComp = victim.getComponent<MdfrComponent>();
    auto vicDefRating = vicMdfrComp->get().weak_at("def_rating");

    return attack::getHitType(rng, attOffRating, vicDefRating);
}

int AttackAction::countDamage(HitType hitType, Actor& attacker, Actor& victim)
{
    auto damage = 0;
    if (hitType != HitType::FAIL)
    {
        auto attMdfrComp = attacker.getComponent<MdfrComponent>();
        auto& attMdfrs = attMdfrComp->get();
        
        auto vicMdfrComp = victim.getComponent<MdfrComponent>();
        auto& vicMdfrs = vicMdfrComp->get();

        damage = attack::getDamage(attMdfrs, vicMdfrs, hitType);
    }
    return damage;
}

void AttackAction::dealDamage(Actor& victim, int damage)
{
    auto vicHpComp = victim.getComponent<HealthComponent>();
    vicHpComp->changeCurrent(-damage);
}

void AttackAction::updateExperience(Actor& attacker, Actor& victim)
{
    auto vicHpComp = victim.getComponent<HealthComponent>();
    if (vicHpComp->getCurr() < 0)
    {
        attack::updateExperience(attacker, victim);
    }
}

void AttackAction::wasteAP(Actor& user)
{
    // FIXME: check AP, magic const to waste
    auto actPtsComp = user.getComponent<ActionPtsComponent>();
    actPtsComp->setCurr(actPtsComp->getCurr() - 1);
}

void AttackAction::updateJournal(Actor& attacker, Actor& victim, HitType hitType, int damage)
{
    attack::updateJournal(attacker, victim, hitType, damage);
}
