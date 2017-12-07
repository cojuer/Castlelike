#pragma once

#include <memory>
#include <string>

#include "widget.h"

class RenderSubsystem;
class ResourceManager;

class Item;

namespace gui {

class TextOwnerWidget;
class Widget;

class ItemHelper : public Widget
{
public:
    ItemHelper();

    bool init();

    void setItem(const Item& item);

    void render(RenderSubsystem& rendSubsys, ResourceManager& resManager) const;

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

    std::unique_ptr<TextOwnerWidget> m_titleSection;
    std::unique_ptr<TextOwnerWidget> m_infoSection;
    std::unique_ptr<TextOwnerWidget> m_primStatsSection;
    std::unique_ptr<TextOwnerWidget> m_secStatsSection;
    std::unique_ptr<TextOwnerWidget> m_descrSection;
};

} /* gui namespace. */