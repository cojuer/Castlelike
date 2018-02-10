#pragma once

#include "component.h"

class ResourceSystem;

class PlayerComponent final : public ActorComponent
{
public:
    static const std::string stringID;

    explicit PlayerComponent(Actor* parent = nullptr);

    void load(Json& node, ResourceSystem& resSystem) override;
    Json save() const override;

    std::string getStringID() const override;

    bool       possess();
    bool       isPossessed() const;

private:
    bool        m_possessed;
};
