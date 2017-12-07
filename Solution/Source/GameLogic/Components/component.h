#pragma once

#include "pugi_aliases.h"
#include "json_aliases.h"

class Actor;
class ResourceManager;

class ActorComponent
{
public:
    explicit ActorComponent(Actor* parent = nullptr);

	virtual void fromJSON(Json& node, ResourceManager& resManager) = 0;
    virtual Json toJSON() const;
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


