#pragma once

#include "component.h"

class StatComponent : public ActorComponent
{
public:
    StatComponent(int base, int current, int max, Actor* parent = nullptr);

    virtual void changeCurrent(int diff);
    void setCurr(int current);
    void setMax(int max);

    virtual void refresh();

    const int& getBase() const;
    const int& getCurr() const;
    const int& getMax() const;

    Json toJSON() const override;

    virtual ~StatComponent();

protected:
    int m_base;
    int m_current;
    int m_max;
};