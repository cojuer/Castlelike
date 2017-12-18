#include "component__stat.h"

#include "actor.h"
    
StatComponent::StatComponent(int base, int current, int max, Actor* parent) :
    ActorComponent(parent),
    m_base(base),
    m_current(current),
    m_max(max)
{}

void StatComponent::changeCurrent(int diff)
{
    if (m_current + diff < 0)
    {
        m_current = 0;
    }
    else if (m_current + diff > m_max)
    {
        m_current = m_max;
    }
    else
    {
        m_current += diff;
    }
}

void StatComponent::setCurr(int current)
{
    m_current = current;
}

void StatComponent::setMax(int max)
{
    m_max = max;
}

void StatComponent::refresh()
{
    /*
    auto attrComponent = m_parent->getComponent<AttrComponent>("attr");
    if (attrComponent)
    {

    }
    auto mdfrComponent = m_parent->getComponent<MdfrComponent>("mdfr");
    if (mdfrComponent)
    {
        
    }
    */
}

const int& StatComponent::getBase() const
{
    return m_base;
}

const int& StatComponent::getCurr() const
{
    return m_current;
}

const int& StatComponent::getMax() const
{
    return m_max;
}

void StatComponent::load(Json& node, ResourceManager& resManager)
{
    m_base = node[0];
    m_current = node[1];
    m_max = node[2];
}

Json StatComponent::save() const
{
    Json node;
    node.push_back(m_base);
    node.push_back(m_current);
    node.push_back(m_max);
    return { { getStringID(), node } };
}

StatComponent::~StatComponent() {}
