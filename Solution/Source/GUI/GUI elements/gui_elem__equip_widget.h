#pragma once

#include <vector>

#include "slot__item.h"
#include "widget.h"

class Equipment;
class Item;

namespace gui {

class EquipmentWidget : public Widget
{
    static std::map<int, std::string> idToType;
    static std::vector<SDL_Rect> slotPos;

public:
    explicit EquipmentWidget(Widget* parent = nullptr);

    void                   load(Json& node, ResourceSystem& resSystem, const Options& opts) override;

    std::vector<ItemSlot>& getSlots();
    Equipment*             getEquipment() const;

    void                   setEquipment(Equipment& equipment);

    bool                   canEquip(int index, Item& item) const;
    bool                   isEquipped(int index) const;
    bool                   equip(int index, Item& item) const;
    void                   unequip(int index) const;

    void                   refresh();

    void                   render(RenderSubsystem& rendSubsystem, ResourceSystem& resSystem, Vec2i coordStart) const override;

private:
    Equipment*        m_equipment;
    std::vector<ItemSlot> m_slots;
};

}