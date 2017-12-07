#pragma once

#include "component.h"

class Behaviour;
class ResourceManager;

class AIComponent final : public ActorComponent
{
public:
    static const std::string stringID;

    explicit AIComponent(Actor* parent = nullptr);
    explicit AIComponent(Behaviour& bhvr, Actor* parent = nullptr);

    void fromJSON(Json& node, ResourceManager& resManager) override;
    std::string getStringID() const override;

    Behaviour* get() const;

    bool       possess();
    bool       isPossessed() const;

    ~AIComponent();

private:
    Behaviour*  m_bhvr;
    bool        m_possessed;
};
