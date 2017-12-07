#pragma once

#include <map>
#include <typeindex>
#include <vector>

#include "component.h"
#include "object.h"
#include "vec2.h"

using ActorID = long long int;

class Actor : public Object
{
	using ComponentMap = std::multimap<std::type_index, ActorComponent*>;

public:
	Actor(ActorID id, const std::string& resID);
    Actor(ActorID id, const std::string& resID, const std::string& type, Coord pos, bool collisive);

    virtual void               setCoord(Coord coord);
    
    ActorID                    getID() const;
    virtual const std::string& getRes() const;
    virtual const Coord&       getCoord() const;
    virtual const std::string& getType() const;

	template<typename T>
	void addComponent(ActorComponent& component)
	{
		component.setParent(*this);
		m_componentMap.insert(std::make_pair(std::type_index(typeid(T)), &component));
	}

	template<typename T>
	T* getComponent() const
	{
		auto iter = m_componentMap.lower_bound(typeid(T));
		if (iter != m_componentMap.end())
		{
			return dynamic_cast<T*>(iter->second);
		}
		else return nullptr;
	}

    virtual bool               isCollisive() const;

    Json toJSON() const;

    virtual ~Actor();

protected:
    ActorID              m_id;
	std::string          m_res;
    // FIXME: delete type
	std::string          m_type;
	ComponentMap         m_componentMap;
};