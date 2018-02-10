#pragma once

#include <memory>

#include "widget.h"

class RenderSubsystem;
class ResourceSystem;

class Item;

namespace gui {

class Widget;

class ItemHelper : public Widget
{
public:
    ItemHelper();

    bool init();

    void setItem(const Item& item);

    void render(RenderSubsystem& rendSubsystem, 
                ResourceSystem& resSystem, 
                Vec2i coordStart) const override;

private:
    void initPrimaryStatsSection(const Item& item);

private:
    static constexpr int s_width = 200;
    static constexpr int s_lMargin = 5;
    static constexpr int s_rMargin = 5;
    static constexpr int s_tMargin = 5;
    static constexpr int s_bMargin = 5;
    static constexpr int s_spacing = 5;

    bool itemHasPrimary;
    bool itemHasSecondary;
    bool itemHasDescription;

    std::unique_ptr<Widget> m_titleSection;
    std::unique_ptr<Widget> m_infoSection;
    std::unique_ptr<Widget> m_primStatsSection;
    std::unique_ptr<Widget> m_secStatsSection;
    std::unique_ptr<Widget> m_descrSection;
};

} /* gui namespace. */