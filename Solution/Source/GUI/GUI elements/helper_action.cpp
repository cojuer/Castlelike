#include "helper_action.h"

#include <string>

#include "item.h"
#include "modifiers.h"
#include "system__resource.h"
#include "subsystem__render.h"
#include "text_renderer.h"
#include "font_data.h"
#include "color.h"

#include "text_manager.h"

namespace gui {

ActionHelper::ActionHelper() :
    Widget(nullptr)
{
    init();
}

bool ActionHelper::init()
{
    m_titleSection.reset(new Widget{ "title", nullptr, { 0 ,0, s_width, 20 }, true });
    m_titleSection->setTextStyle({ Font::latoBold, FontSize::large, Color::silver, s_width - 2 * s_lMargin });
    m_infoSection.reset(new Widget("itype", nullptr, { 0, 0, s_width, 60}, true));
    m_infoSection->setTextStyle({ Font::latoRegular, FontSize::medium, Color::silver, s_width - 2 * s_lMargin });
    return true;
}

void ActionHelper::setAction(const std::string& id)
{
    m_titleSection->setText(TextManager::instance().getName(id));
    m_infoSection->setText(TextManager::instance().getDescription(id));
}

void ActionHelper::render(RenderSubsystem& rendSubsystem,
    ResourceSystem& resSystem,
    Vec2i coordStart) const
{
    int x, y;
    SDL_GetMouseState(&x, &y);

    std::string iclass = "delete";
    std::string strdamage = "delete";

    Vec2i pos(x - s_width, y - 65);
    if (pos.x < 0) { pos.x = 0; }
    if (pos.y < 0) { pos.y = 0; }

    auto height = s_tMargin;
    height += m_titleSection->getHeight() + s_spacing;
    height += m_infoSection->getHeight() + s_spacing;
    height += s_bMargin;

    auto texture = resSystem.get<Renderable>("helper_back");
    SDL_Rect dst = { pos.x, pos.y, s_width, height };
    rendSubsystem.render(texture, dst);

    int curHeight = s_tMargin;

    m_titleSection->setGeometry({ 
        s_lMargin, 
        curHeight, 
        m_titleSection->getWidth() - 2 * s_lMargin, 
        m_titleSection->getHeight() 
    });
    m_titleSection->render(rendSubsystem, resSystem, pos);
    curHeight += m_titleSection->getHeight() + s_spacing;

    m_infoSection->setGeometry({
        s_lMargin,
        curHeight,
        m_infoSection->getWidth() - 2 * s_lMargin,
        m_infoSection->getHeight()
    });
    m_infoSection->render(rendSubsystem, resSystem, pos);
    curHeight += m_infoSection->getHeight() + s_spacing;
}

} /* gui namespace */