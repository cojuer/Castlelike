#pragma once

#include <memory>
#include <string>

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

    void render(RenderSubsystem& rendSubsys, ResourceSystem& resSystem) const;

    ~ItemHelper();

private:
    void initPrimaryStatsSection(const Item& item);

private:
    static constexpr int width = 200;
    static constexpr int lMargin = 5;
    static constexpr int rMargin = 5;
    static constexpr int tMargin = 5;
    static constexpr int bMargin = 5;
    static constexpr int spacing = 5;

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