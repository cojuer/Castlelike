#pragma once

#include "component.h"
#include "transform.h"

class ResourceSystem;

class TransformComponent final : public ActorComponent
{
public:
    static const std::string stringID;

    explicit TransformComponent(Actor* parent = nullptr);

    void load(Json& node, ResourceSystem& resSystem) override;
    Json save() const override;

    std::string getStringID() const override;

    const Transform& get() const;
    void             set(Transform transform);

private:
    Transform m_transform;
};