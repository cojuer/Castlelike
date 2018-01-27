#include "gui_elem__equip_widget.h"

#include "atexture.h"
#include "equipment.h"
#include "GUI/Behaviour/behaviour.h"

#include "system__resource.h"

namespace gui {

std::map<int, std::string> EquipmentWidget::idToType =
{
    { 0, "head" },
    { 1, "shoulders" },
    { 2, "chest" },
    { 3, "legs" },
    { 4, "wrist" },
    { 5, "hands" },
    { 6, "waist" },
    { 7, "feet" },
    { 8, "lhand" },
    { 9, "rhand" }
};

std::vector<SDL_Rect> EquipmentWidget::slotPos = 
{
    {21, 28, 48, 48},
    {21, 80, 48, 48},
    {21, 132, 48, 48},
    {21, 184, 48, 48},
    {281, 28, 48, 48},
    {281, 80, 48, 48},
    {281, 132, 48, 48},
    {281, 184, 48, 48},
    {125, 184, 48, 48},
    {177, 184, 48, 48}
};

EquipmentWidget::EquipmentWidget(Widget* parent) :
    Widget(parent),
    m_equipment(nullptr)
{}

void EquipmentWidget::load(Json& node, ResourceSystem& resSystem, const Options& opts)
{
    loadGeometry(node, opts);
    loadOptions(node);
    loadGraphics(node, resSystem);
    m_slots.reserve(slotPos.size());
    for (size_t i = 0; i < slotPos.size(); ++i)
    {
        m_slots.emplace_back(idToType[i], this, slotPos[i]);
    }
}

void EquipmentWidget::setEquipment(Equipment& equipment)
{
    m_equipment = &equipment;
    refresh();
}

bool EquipmentWidget::canEquip(int index, Item& item) const
{
    return m_equipment->canEquip(idToType[index], item);
}

bool EquipmentWidget::isEquipped(int index) const
{
    return m_equipment->isEquipped(idToType[index]);
}

bool EquipmentWidget::equip(int index, Item& item) const
{
    return m_equipment->equip(idToType[index], item);
}

void EquipmentWidget::unequip(int index) const
{
    m_equipment->unequip(idToType[index]);
}

void EquipmentWidget::refresh()
{
    for (size_t i = 0; i < m_slots.size(); ++i)
    {
        auto item = m_equipment->getItem(idToType[i]);
        if (item)
        {
            m_slots[i].setItem(*item);
        }
        else
        {
            m_slots[i].eraseItem();
        }
    }
}

std::vector<ItemSlot>& EquipmentWidget::getSlots()
{
    return m_slots;
}

void EquipmentWidget::render(RenderSubsystem& rendSubsystem, ResourceSystem& resSystem, Vec2i coordStart) const
{
    if (!m_visible) return;

    coordStart += getPos();

    for (auto& slot : m_slots)
    {
        slot.render(rendSubsystem, resSystem, coordStart);
    }
}

Equipment* EquipmentWidget::getEquipment() const
{
    return m_equipment;
}

} /* gui namespace. */