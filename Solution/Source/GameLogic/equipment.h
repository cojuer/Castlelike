#pragma once

#include <map>
#include <vector>

class Item;

class Equipment
{
    using StrToItemMap = std::map<std::string, Item*>;

public:
    Equipment();

    bool  equip(Item& item);
    bool  equip(const std::string& slotType, Item& item);
    void  unequip(const std::string& slotType);

    Item* getItem(const std::string& slotType) const;

    bool  isEquipped(const std::string& slotType) const;
    bool  canEquip(const Item& item);
    bool  canEquip(const std::string& slotType, const Item& item);
    bool  hasItem(std::string resID) const;

    std::string slotFor(Item& item) const;

    const static std::vector<std::string> types;

private:
    StrToItemMap m_slots;
};
