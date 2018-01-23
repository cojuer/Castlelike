#include "bagwidget.h"

#include "container.h"
#include "subsystem__render.h"
#include "system__resource.h"

namespace gui {

BagWidget::BagWidget(Widget* parent) :
    Widget(parent),
    m_container(nullptr),
    m_activeSlot(nullptr)
{}

void BagWidget::init(Json& node, ResourceSystem& resSystem)
{
    loadGeometry(node);
    loadGraphics(node, resSystem);
    loadOptions(node);
    if (!m_opts.count("lmargin")) m_opts["lmargin"] = lMargin;
    if (!m_opts.count("tmargin")) m_opts["tmargin"] = tMargin;
    if (!m_opts.count("indent"))  m_opts["indent"] = indent;
    m_slots.reserve(m_opts["rows"] * m_opts["cols"]);
    for (int i = 0; i < m_opts["rows"]; ++i)
    {
        for (int j = 0; j < m_opts["cols"]; ++j)
        {
            auto x = m_opts.at("lmargin") + (defaultSlotWidth + m_opts.at("indent")) * j;
            auto y = m_opts.at("tmargin") + (defaultSlotHeight + m_opts.at("indent")) * i;
            SDL_Rect geometry = { x, y, defaultSlotWidth, defaultSlotHeight };
            m_slots.emplace_back(std::to_string(i) + ":" + std::to_string(j), this, geometry);
        }
    }
}

std::vector<ItemSlot>& BagWidget::getSlots()
{
    return m_slots;
}

void BagWidget::setContainer(Container* container)
{
    m_container = container;
    refresh();
}

void BagWidget::refresh()
{
    if (m_container)
    {
        for (int i = 0; i < m_opts.at("rows") * m_opts.at("cols"); ++i)
        {
            m_slots[i].eraseItem();
        }
        for (int i = 0; i < m_container->getSize() && i < m_opts.at("rows") * m_opts.at("cols"); ++i)
        {
            auto item = m_container->getSlot(i);
            if (item)
            {
                m_slots[i].setItem(*item);
            }
        }
    }
}

Container* BagWidget::getContainer() const
{
    return m_container;
}

void BagWidget::render(RenderSubsystem& rendSubsystem, ResourceSystem& resSystem, Vec2i coordStart) const
{
    if (!m_visible) return;

    auto dst = m_geometry;
    rendSubsystem.render(m_rendered, dst);
    coordStart += getPos();
    for (int i = 0; i < m_opts.at("cols") * m_opts.at("rows"); ++i)
    {
        if (&m_slots[i] != m_activeSlot)
        {
            m_slots[i].render(rendSubsystem, resSystem, coordStart);
        }
    }
}

void BagWidget::resetSlots()
{
    for (int i = 0; i < m_opts.at("rows") * m_opts.at("cols"); ++i)
    {
        m_slots[i].setPressed(false);
    }
}

} /* gui namespace. */