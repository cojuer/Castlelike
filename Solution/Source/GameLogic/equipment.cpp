#include "equipment.h"

#include "item.h"

#include <iostream>
#include <string>
#include <cassert>

const std::vector<std::string> Equipment::types =
{
    "head",    "chest",       "wrist",
    "legs",    "waist",       "feet",
    "hands",   "shoulders",   "lhand",
    "rhand"
};

Equipment::Equipment()
{
    for (auto& type: types)
    {
        m_slots[type] = nullptr;
    }
}

// FIXME: use for weapons
bool Equipment::equip(Item& item)
{
    if (item.isWeapon())
    {
        m_slots["lhand"] = &item;
    }
    if (item.isArmour())
    {
        assert(m_slots.find(item.getType()) != m_slots.end() && "Armour type invalid");
        m_slots[item.getType()] = &item;
        return true;
    }
    return false;
}

Item* Equipment::getItem(const std::string& slotType) const
{
    return m_slots.at(slotType);
}

bool Equipment::canEquip(const std::string& slotType, const Item& item)
{
    // FIXME: rework
    auto itemClass = item.getClass();
    if (slotType == "lhand") 
    {
        return (itemClass == std::string("weapon"));
    } 
    else if (slotType == "rhand") 
    {
        return (itemClass == std::string("weapon"));
    } 
    else
    {
        // TODO: delete
        std::cout << slotType << ":" << item.getType() << std::endl;
        return (slotType == item.getType());
    }
}

bool Equipment::hasItem(std::string resID) const
{
    for (auto& slot : m_slots)
    {
        if (slot.second && slot.second->getRes() == resID)
        {
            return true;
        }
    }
    return false;
}

std::string Equipment::slotFor(Item& item) const
{
    if (item.isWeapon())
    {
        return "lhand";
    }
    else if (item.isArmour())
    {
        assert(m_slots.find(item.getType()) != m_slots.end() && "Armour type invalid");
        return item.getType();
    }
    return "";
}

bool Equipment::isEquipped(const std::string& slotType) const
{
    return m_slots.find(slotType) != m_slots.end() &&
           m_slots.at(slotType) != nullptr;
}

bool Equipment::canEquip(const Item& item)
{
    if (item.isWeapon())
    {
        return true;
    }
    else if (item.isArmour())
    {
        assert(m_slots.find(item.getType()) != m_slots.end() && "Armour type invalid");
        return true;
    }
    return false;
}

bool Equipment::equip(const std::string& slotType, Item& item)
{
    if (canEquip(slotType, item))
    {
        m_slots[slotType] = &item;
        return true;
    }
    return false;
}

void Equipment::unequip(const std::string& slotType)
{
    m_slots[slotType] = nullptr;
}