#pragma once

#include "action_interface.h"
#include "action_utils.h"

class Actor;

class AttackAction : public ActionInterface
{
public:
    AttackAction(ActionArgs&& args = {});
    virtual ~AttackAction() = default;

    virtual void act() override;

    void setArg(std::string argType, std::any arg) override;

    virtual std::vector<std::string> getRequiredArgTypes() const override;
    virtual bool canAct() const override;

protected:
    virtual std::vector<Actor*> getVictims() const;
    virtual HitType             chooseHitType(const Actor& attacker, const Actor& victim, RNG& rng) const;
    virtual int                 countDamage(HitType hitType, Actor& attacker, Actor& victim);
    virtual void                dealDamage(Actor& victim, int damage);
    virtual void                updateExperience(Actor& attacker, Actor& victim);
    virtual void                updateJournal(Actor& attacker, Actor& victim, HitType hitType, int damage);
    virtual void                wasteAP(Actor& user);

protected:
    ActionArgs  m_args;
};