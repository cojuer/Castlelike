#pragma once

#include "pugi_aliases.h"
#include "json_aliases.h"

class Actor;
class ResourceSystem;

class ActorComponent
{
public:
    explicit ActorComponent(Actor* parent = nullptr);

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

    virtual ~ActorComponent();

protected:
    Actor*      m_parent;
};

template <class T>
ActorComponent* ActorComponent::create()
{
    return new T();
}


