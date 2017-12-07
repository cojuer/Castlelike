#pragma once

#include "attributes.h"
#include "component.h"

class ResourceManager;

class AttrComponent final : public ActorComponent
{
    friend class AttrComponentJsonParser;

public:
    static const std::string stringID;

    explicit AttrComponent(Actor* parent = nullptr);
	explicit AttrComponent(const Attributes& attrs, Actor* parent = nullptr);

	void fromJSON(Json& node, ResourceManager& resManager) override;
    Json toJSON() const override;
    std::string getStringID() const override;

	const Attributes& get() const;

    ~AttrComponent();
    
private:
    Attributes  m_attrs;
	unsigned    m_points;
};
