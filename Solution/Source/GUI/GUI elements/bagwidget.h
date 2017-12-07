#pragma once

#include <vector>

#include "widget.h"
#include "slot__item.h"

class Container;

namespace gui {

class ATexture;

class BagWidget : public Widget
{
    static constexpr int lMargin = 20;
    static constexpr int tMargin = 20;
    static constexpr int indent = 20;

public:
    explicit BagWidget(Widget* parent = nullptr);

    void init(Json& node, ResourceManager& resManager) override;

    void                    setContainer(Container* container);

    std::vector<ItemSlot>&  getSlots();//cannot make it const
    Container*              getContainer() const;

    void                    refresh();
    void                    resetSlots();

    void                    render(RenderSubsystem& rendSubsystem, ResourceManager& resManager, Vec2i coordStart = { 0, 0 }) const override;

private:
    Container*              m_container;
    std::vector<ItemSlot>   m_slots;

    const ItemSlot*         m_activeSlot;
};

}