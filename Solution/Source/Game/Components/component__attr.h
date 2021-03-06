#pragma once

#include "attributes.h"
#include "component.h"

class ResourceSystem;

class AttrComponent final : public ActorComponent
{
    friend class AttrComponentJsonParser;

public:
    static const std::string stringID;

    explicit AttrComponent(Actor* parent = nullptr);
	explicit AttrComponent(Attributes attrs, Actor* parent = nullptr);

	void load(Json& node, ResourceSystem& resSystem) override;
    Json save() const override;

    std::string getStringID() const override;

	const Attributes& get() const;
    
private:
    Attributes  m_attrs;
	unsigned    m_points;
};
