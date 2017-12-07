#include "component__stateful_graphics.h"
//
//#include "resource_manager.h"
//#include "actor.h"
//
//const std::string StatefulGraphicsComponent::stringID = "stateful_graphics";
//
//StatefulGraphicsComponent::StatefulGraphicsComponent(Layer layer, std::vector<std::string> renderableIds, Actor* parent) :
//    GraphicsInterfaceComponent(layer, parent),
//    m_state(0),
//    m_renderableIds(renderableIds)
//{}
//
//StatefulGraphicsComponent::StatefulGraphicsComponent(Actor* parent) :
//    GraphicsInterfaceComponent(Layer::TILE, parent),
//    m_state(0)
//{}
//
//void StatefulGraphicsComponent::fromJSON(Json& node, ResourceManager& resManager)
//{
//    m_state = 0;
//    for (auto& rendNode : node)
//    {
//        m_renderableIds.push_back(rendNode);
//    }
//}
//
//std::string StatefulGraphicsComponent::getStringID() const
//{
//    return stringID;
//}
//
//void StatefulGraphicsComponent::setState(const std::string& state)
//{
//    assert(m_renderableIds.find(state) != m_renderableIds.end() 
//        && "StatefulGraphicsComponent: error: invalid graphics state");
//    
//    m_state = state;
//}
//
//const std::string& StatefulGraphicsComponent::getState() const
//{
//    return m_state;
//}
//
//std::string StatefulGraphicsComponent::get() const
//{
//    return m_renderableIds.at(m_state);
//}
//
//StatefulGraphicsComponent::~StatefulGraphicsComponent() {}
