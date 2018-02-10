#pragma once

#include "component.h"
#include "container.h"

class ResourceSystem;

class ContainerInterfaceComponent : public ActorComponent
{
public:
    static const std::string stringID;

    explicit ContainerInterfaceComponent(Actor* parent = nullptr);
    explicit ContainerInterfaceComponent(Container&& container, Actor* parent = nullptr);

    ContainerInterfaceComponent(const ContainerInterfaceComponent&) = delete;
    ContainerInterfaceComponent(ContainerInterfaceComponent&&) = delete;
    ContainerInterfaceComponent& operator=(const ContainerInterfaceComponent&) = delete;
    ContainerInterfaceComponent& operator=(ContainerInterfaceComponent&&) = delete;

    virtual ~ContainerInterfaceComponent();

    bool add(Item& item);
    bool addToSlot(Item& item, int index);
    void eraseSlot(int index);
    void swapSlots(int fstIndex, int sndIndex);
    void takeFrom(Container& cont);

    bool             changeGold(int& diff);
    bool             takeGold(Container& cont);

    int              getSize() const;
    Item*            getSlot(int index) const;
    unsigned int     getItemsNumber() const;
    const int&       getGold() const;

    bool             hasItem(const std::string& id) const;

    bool             isEmpty() const;
    bool             isFull() const;

protected:
    Container  m_container;
};