#include "item.h"
#include "text_manager.h"

Item::Item(std::shared_ptr<const ItemProto>& proto) :
    m_amount(1),
    m_prototype(proto)
{}

uint32_t Item::getMaxCount() const
{
    return m_prototype->m_maxAmount;
}

bool Item::combine(Item& item)
{
    if (item.getRes() == getRes() &&
        getMaxCount() > m_amount)
    {
        uint32_t excess = m_amount + item.m_amount > getMaxCount() ?
                          m_amount + item.m_amount - getMaxCount() :
                          0;
        m_amount += item.m_amount - excess;
        item.m_amount = excess;
        return (item.m_amount == 0);
    }
    return false;
}

void Item::setAmount(uint32_t amount)
{
    assert(amount < getMaxCount() && "Item: amount not limited");
    m_amount = amount;
}

const std::string& Item::getClass() const
{
    return m_prototype->m_class;
}

const std::string& Item::getType() const
{
    return m_prototype->m_type;
}

const std::string& Item::getName() const
{
    return TextManager::instance().getName(m_prototype->m_resID);
}

const std::string& Item::getRes() const
{
    return m_prototype->m_resID;
}

const uint32_t& Item::getLevel() const
{
    return m_prototype->m_level;
}

const uint32_t& Item::getValue() const
{
    return m_prototype->m_value;
}

const Modifiers& Item::getMdfrs() const
{
    return *m_prototype->m_modifiers;
}

Action* Item::getAction() const
{
    return m_prototype->m_action;
}

const uint32_t& Item::getCount() const
{
    return m_amount;
}

const std::string& Item::getDesc() const
{
    return TextManager::instance().getDescription(m_prototype->m_resID);
}

bool Item::isWeapon() const
{
    return (m_prototype->m_class == std::string("weapon"));
}

bool Item::isArmour() const
{
    return (m_prototype->m_class == std::string("medium_armor") ||
            m_prototype->m_class == std::string("heavy_armor"));
}

bool Item::isStackable() const
{
    return m_prototype->m_maxAmount > 1;
}

bool Item::isConsumable() const
{
    return m_prototype->m_consumable;
}
