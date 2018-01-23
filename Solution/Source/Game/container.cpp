#include "container.h"

#include <cassert>
#include <iostream>

Container::Container(int maxsize) :
    m_size(maxsize),
    m_gold(0)
{
    auto end = m_empties.end();
    for (auto i = 0; i < m_size; ++i)
    {
        m_empties.insert(end, i);
    }
}

bool Container::add(Item& item)
{
    for (auto& pair : m_busyslots)
    {
        if (pair.second->combine(item))
        {
            // check amount, delete item if amount == 0
            return true;
        }
    }
    if (isFull()) return false;
    m_busyslots[*m_empties.begin()] = &item;
    m_empties.erase(m_empties.begin());
    return true;
}

int Container::getSize() const
{
    return m_size;
}

Item* Container::getSlot(int index) const
{
    if (m_busyslots.find(index) != m_busyslots.end())
    {
        return m_busyslots.at(index);
    }
    return nullptr;
}

void Container::eraseSlot(int index)
{
    assert(index < m_size && "Container::eraseSlot: error: index out of range");
    m_busyslots.erase(index);
    m_empties.insert(index);
}

unsigned int Container::getItemsNumber() const
{
    return m_busyslots.size();
}

const int& Container::getGold() const
{
    return m_gold;
}

bool Container::hasItem(const std::string id) const
{
    for (auto& slot : m_busyslots)
    {
        if (id == slot.second->getRes())
        {
            return true;
        }
    }
    return false;
}

void Container::swapSlots(int fstIndex, int sndIndex)
{
    assert(fstIndex != sndIndex && "Container::swapSlots: warning: indices of slots to swap are equal");
    std::swap(m_busyslots[fstIndex], m_busyslots[sndIndex]);
    if (!m_busyslots.at(fstIndex))
    {
        eraseSlot(fstIndex);
    }
    if (!m_busyslots.at(sndIndex))
    {
        eraseSlot(sndIndex);
    }
}

void Container::takeFrom(Container& cont)
{
    for (auto& pair : cont.m_busyslots)
    {
        add(*pair.second);
    }
    // FIXME: does not updates empty slots
    cont.m_busyslots.erase(cont.m_busyslots.begin(), cont.m_busyslots.end());
}

bool Container::addToSlot(Item& item, int index)
{
    if (m_busyslots.find(index) != m_busyslots.end())
    {
        return m_busyslots[index]->combine(item);
    }
    else
    {
        m_busyslots[index] = &item;
        m_empties.erase(m_empties.begin());
        return true;
    }
}

bool Container::changeGold(int& diff)
{
    if (m_gold + diff < 0) return false;
    if (m_gold + diff > maxGold)
    {
        diff = m_gold + diff - maxGold;
        m_gold = maxGold;
        return true;
    }

    m_gold += diff;
    diff = 0;
    return true;
}

bool Container::takeGold(Container& cont)
{
    if (m_gold + cont.m_gold > maxGold)
    {
        cont.m_gold = m_gold + cont.m_gold - maxGold;
        m_gold = maxGold;
        return true;
    }

    m_gold += cont.m_gold;
    cont.m_gold = 0;
    return true;
}

// FIXME: should container delete items?
Container::~Container()
{
    m_busyslots.erase(m_busyslots.begin(), m_busyslots.end());
}

bool Container::isEmpty() const
{
    return m_busyslots.size() == 0;
}

bool Container::isFull() const
{
    return m_busyslots.size() == m_size;
}