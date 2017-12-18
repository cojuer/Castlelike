#pragma once

#include "component.h"

class ResourceManager;

class PlayerComponent final : public ActorComponent
{
public:
    static const std::string stringID;

    explicit PlayerComponent(Actor* parent = nullptr);

    void fromJSON(Json& node, ResourceManager& resManager) override;
    Json toJSON() const override;
    std::string getStringID() const override;

    bool       possess();
    bool       isPossessed() const;

    ~PlayerComponent();

private:
    bool        m_possessed;
};
