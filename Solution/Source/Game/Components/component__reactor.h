#pragma once

#include <map>

#include "component__reactor_interface.h"
#include "actor.h"

class ResourceSystem;
  
class ReactorComponent final : public ReactorComponentInterface
{
    using Reactions = std::multimap<std::string, Reaction>;
    
public:
    static const std::string stringID;

    explicit ReactorComponent(Actor* parent = nullptr);

	void load(Json& node, ResourceSystem& resSystem) override;
    Json save() const override;

    std::string getStringID() const override;

    void addReaction(std::string condition, Reaction&& reaction);

    void react(const std::string& condition, ActionArgs input) override;

    ~ReactorComponent();

private:
    Reactions m_reactions;
};