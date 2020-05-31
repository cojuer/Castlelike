#pragma once

#include <memory>

#include "widget.h"

class RenderSubsystem;
class ResourceSystem;

class Item;

namespace gui {

    class Widget;

class ActionHelper : public Widget
{
public:
    ActionHelper();

    bool init();

    void setAction(const std::string& id);

    void render(
        RenderSubsystem& rendSubsystem,
        ResourceSystem& resSystem,
        Vec2i coordStart
    ) const override;

private:
    static constexpr int s_width = 250;
    static constexpr int s_lMargin = 5;
    static constexpr int s_rMargin = 5;
    static constexpr int s_tMargin = 5;
    static constexpr int s_bMargin = 5;
    static constexpr int s_spacing = 5;

    std::unique_ptr<Widget> m_titleSection;
    std::unique_ptr<Widget> m_infoSection;
};

} /* gui namespace. */
