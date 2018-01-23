#include "slot__item.h"

#include "atexture.h"
#include "item.h"
#include "system__resource.h"
#include "subsystem__render.h"
#include "widget__number.h"

namespace gui {

ItemSlot::ItemSlot(const std::string& name, Widget* parent, SDL_Rect geometry) :
    Slot(name, parent, geometry, SlotType::ITEM),
    m_item(nullptr)
{
    // FIXME: magic consts
    auto itemNumWdg = new NumberWidget("num", this, { 20, 20, 10, 10 }, true, nullptr);
    Widget::addChild(*itemNumWdg);
}

void ItemSlot::setItem(Item& item)
{
    m_item = &item;
    if (m_item->getMaxCount() > 1)
    {
        dynamic_cast<NumberWidget*>(m_children["num"].get())->setData(m_item->getCount());
    }
}

bool ItemSlot::handle(SDL_Event& event, Vec2i coordStart)
{
    if (event.button.button == SDL_BUTTON_LEFT &&
        (event.type == SDL_MOUSEBUTTONDOWN ||
        event.type == SDL_MOUSEBUTTONUP))
    {
        int x, y;
        SDL_GetMouseState(&x, &y);

        if (isPointOn({ x, y }, coordStart))
        {
            switch (event.type)
            {
            case SDL_MOUSEBUTTONDOWN:
                m_pressed = true;
                break;
            case SDL_MOUSEBUTTONUP:
                m_pressed = false;
                break;
            default:
                break;
            }
        }
        else if (m_pressed == true && event.type == SDL_MOUSEBUTTONUP)
        {
            m_pressed = false;
        }
    }
    return m_pressed;
}

void ItemSlot::eraseItem()
{
    m_item = nullptr;
    dynamic_cast<NumberWidget*>(m_children["num"].get())->eraseData();
}

Item* ItemSlot::getItem() const
{
    return m_item;
}

bool ItemSlot::isEmpty() const
{
    return (m_item == nullptr);
}

void ItemSlot::render(RenderSubsystem& rendSubsystem, ResourceSystem& resSystem, Vec2i coordStart) const
{
    if (m_rendered)
    {
        renderSelf(rendSubsystem, resSystem, coordStart);
    }
    if (m_item)
    {
        auto texture = resSystem.get<Renderable>(m_item->getRes());
        SDL_Rect dstRect = {
            m_geometry.x + (m_geometry.w - texture->getWidth()) / 2,
            m_geometry.y + (m_geometry.h - texture->getHeight()) / 2,
            texture->getWidth(),
            texture->getHeight()
        };
        dstRect.x += coordStart.x;
        dstRect.y += coordStart.y;
        Vec2i childCoord{ coordStart };
        if (m_pressed)
        {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            dstRect.x = mouseX - texture->getWidth() / 2;
            dstRect.y = mouseY - texture->getHeight() / 2;
            childCoord = Vec2i{ dstRect.x, dstRect.y } - getPos();
        }
        rendSubsystem.render(texture, dstRect);
        renderChildren(rendSubsystem, resSystem, childCoord);
    }
}

void ItemSlot::setPressed(bool state)
{
    m_pressed = state;
}

} /* gui namespace. */