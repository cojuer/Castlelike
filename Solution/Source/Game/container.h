#pragma once

#include <set>

#include "item.h"

/**
 * Possible optimizations:
 * 1) use first empty index
 * 2) use set of empty slots(slow creation, fast usage) 
 * 3) use stackables map to combine stacks faster
 */
class Container
{
public:
    explicit Container(int size);

    /**
     * \brief try to add item to the container.
     * 
     * \return true if item has been succesfully added to 
     * the container, else false.
     */
    bool add(Item& item);

    /**
    * \brief try to add item to the container slot 
    * with given index.
    *
    * \return true if item has been succesfully added to
    * the container at given index, else false.
    */
    bool addToSlot(Item& item, int index);

    /**
     * \brief erase contents of slot with given index.
     * 
     * \param index valid slot index(< container size).
     */
    void eraseSlot(int index);

    /**
     * \brief swap contents of slots with given indeces.
     * 
     * \param fstIndex valid slot index(< container size).
     * \param sndIndex valid slot index(< container size), 
     * different from fstIndex.
     */
    void swapSlots(int fstIndex, int sndIndex);

    /**
     * \brief take all items from another container and 
     * erase its slots.
     * 
     * \param cont reference to the container.
     */
    void takeFrom(Container& cont);

    // FIXME: methods aren't intuitive
    bool             changeGold(int& diff);
    bool             takeGold(Container& cont);

    int              getSize() const;
    Item*            getSlot(int index) const;
    unsigned int     getItemsNumber() const;
    const int&       getGold() const;

    bool             hasItem(const std::string& resID) const;

    bool             isEmpty() const;
    bool             isFull() const;

    ~Container();

private:
    // TODO: use unique pointers
    std::map<int, Item*> m_busyslots;
    std::set<int>      m_empties;
    int                m_size;
    int                m_gold;

    static constexpr int maxGold = 1000000000;

    friend class BagComponent;
    friend class LootComponent;
};