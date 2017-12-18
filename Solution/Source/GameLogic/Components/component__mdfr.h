#pragma once

#include "component.h"
#include "modifiers.h"

class ResourceManager;

class MdfrComponent final : public ActorComponent
{
public:
    static const std::string stringID;

    explicit MdfrComponent(Actor* parent = nullptr);
	explicit MdfrComponent(const Modifiers& base, Actor* parent = nullptr);

	void load(Json& node, ResourceManager& resManager) override;
    void postLoad(ResourceManager& resManager) override;
    Json save() const override;
    std::string getStringID() const override;

    void refresh();

	const Modifiers& getBase() const;
	const Modifiers& get() const;

    ~MdfrComponent();

private:
    Modifiers m_base;
    Modifiers m_current;
};