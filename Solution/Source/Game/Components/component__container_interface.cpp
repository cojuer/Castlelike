#include "component__container_interface.h"

ContainerInterfaceComponent::ContainerInterfaceComponent(Actor* parent) :
    ActorComponent(parent),
    m_container(36)
{}

ContainerInterfaceComponent::ContainerInterfaceComponent(Container&& container, Actor* parent) :
    ActorComponent(parent),
    m_container(std::move(container))
{}

bool ContainerInterfaceComponent::add(Item& item)
{
    return m_container.add(item);
}

bool ContainerInterfaceComponent::addToSlot(Item& item, int index)
{
    return m_container.addToSlot(item, index);
}

void ContainerInterfaceComponent::eraseSlot(int index)
{
    m_container.eraseSlot(index);
}

void ContainerInterfaceComponent::swapSlots(int fstIndex, int sndIndex)
{
    m_container.swapSlots(fstIndex, sndIndex);
}

void ContainerInterfaceComponent::takeFrom(Container& cont)
{
    m_container.takeFrom(cont);
}

bool ContainerInterfaceComponent::changeGold(int& diff)
{
    return m_container.changeGold(diff);
}

bool ContainerInterfaceComponent::takeGold(Container& cont)
{
    return m_container.takeGold(cont);
}

int ContainerInterfaceComponent::getSize() const
{
    return m_container.getSize();
}

Item* ContainerInterfaceComponent::getSlot(int index) const
{
    return m_container.getSlot(index);
}

unsigned int ContainerInterfaceComponent::getItemsNumber() const
{
    return m_container.getItemsNumber();
}

const int& ContainerInterfaceComponent::getGold() const
{
    return m_container.getGold();
}

bool ContainerInterfaceComponent::hasItem(const std::string& id) const
{
    return m_container.hasItem(id);
}

bool ContainerInterfaceComponent::isEmpty() const
{
    return m_container.isEmpty();
}

bool ContainerInterfaceComponent::isFull() const
{
    return m_container.isFull();
}

ContainerInterfaceComponent::~ContainerInterfaceComponent() = default;
