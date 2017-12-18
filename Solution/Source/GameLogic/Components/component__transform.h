#pragma once

#include "component.h"
#include "transform.h"

class ResourceManager;

class TransformComponent final : public ActorComponent
{
public:
    static const std::string stringID;

    explicit TransformComponent(Actor* parent = nullptr);

    Json save() const override;
    void load(Json& node, ResourceManager& resManager) override;
    std::string getStringID() const override;

    const Transform& get() const;
    void             set(Transform transform);

    ~TransformComponent();

private:
    Transform m_transform;
};