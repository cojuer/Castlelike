#pragma once

#include "component.h"

class StatComponent : public ActorComponent
{
public:
    StatComponent(int base, int current, int max, Actor* parent = nullptr);

    StatComponent(const StatComponent&) = delete;
    StatComponent(StatComponent&&) = delete;
    StatComponent& operator=(const StatComponent&) = delete;
    StatComponent& operator=(StatComponent&&) = delete;

    virtual ~StatComponent() = default;

    void load(Json& node, ResourceSystem& resSystem) override;
    Json save() const override;

    virtual void changeCurrent(int diff);
    void setCurr(int current);
    void setMax(int max);

    virtual void refresh();

    const int& getBase() const;
    const int& getCurr() const;
    const int& getMax() const;

protected:
    int m_base;
    int m_current;
    int m_max;
};