#pragma once

#include "item_prototype.h"
#include <memory>

struct Action;
struct Effect;
class ItemProto;

class Item
{
public:
    static constexpr int chargesInf = 100000;

    Item() = delete;
    explicit Item(std::shared_ptr<const ItemProto>& proto);

    const std::string&   getClass() const;
    const std::string&   getType() const;
    const std::string&   getName() const;
    const std::string&   getRes() const;
    const std::string&   getDesc() const;
    const int&           getLevel() const;
    const int&           getValue() const;
    const Modifiers&     getMdfrs() const;
    Action*              getAction() const;
    const int&           getCount() const;
    int                  getMaxCount() const;

    bool                 combine(Item& item);
    void                 setAmount(uint32_t amount);

    bool                 isWeapon() const;
    bool                 isArmour() const;
    bool                 isStackable() const;
    bool                 isConsumable() const;

protected:
    int m_amount;

    std::shared_ptr<const ItemProto> m_prototype;
};