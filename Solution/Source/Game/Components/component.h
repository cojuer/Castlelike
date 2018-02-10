#pragma once

#include "json_aliases.h"

class Actor;
class ResourceSystem;

class ActorComponent
{
public:
    explicit ActorComponent(Actor* parent = nullptr);

    ActorComponent(const ActorComponent&) = delete;
    ActorComponent(ActorComponent&&) = delete;
    ActorComponent& operator=(const ActorComponent&) = delete;
    ActorComponent& operator=(ActorComponent&&) = delete;

    virtual ~ActorComponent();

    /**
     * \brief Generate from template
     */
    virtual void generate(Json& node, ResourceSystem& resSystem);
    virtual void postGenerate(ResourceSystem& resSystem);
	virtual void load(Json& node, ResourceSystem& resSystem) = 0;
    /**
     * postLoad() can use parent actor, while in load() it can be nullptr
     */
    virtual void postLoad(ResourceSystem& resSystem);
    virtual Json save() const = 0;

    virtual std::string getStringID() const = 0;

    virtual void setParent(Actor& parent);

    Actor*       getParent() const;

    template<class T> static ActorComponent* create();

protected:
    Actor*      m_parent;
};

template <class T>
ActorComponent* ActorComponent::create()
{
    return new T();
}


