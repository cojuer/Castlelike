#include "helper_item.h"

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

ItemHelper::ItemHelper() :
    Widget(nullptr),
    itemHasPrimary(false),
    itemHasSecondary(false),
    itemHasDescription(false)
{
    init();
}

bool ItemHelper::init()
{
    // FIXME: magic const
    uint32_t width = 200;
    m_titleSection.reset(new Widget{ "title", nullptr, { 0 ,0, 200, 20 }, true });
    m_titleSection->setTextStyle({ Font::latoBold, FontSize::large, Color::silver, width });
    m_infoSection.reset(new Widget("itype", nullptr, { 0, 0, 200, 20 }, true));
    m_infoSection->setTextStyle({ Font::latoRegular, FontSize::medium, Color::silver, width });
    m_primStatsSection.reset(new Widget("prim_stat", nullptr, { 0 ,0, 200, 20 }, true));
    m_primStatsSection->setTextStyle({ Font::latoBold, FontSize::medium, Color::silver, width });
    m_secStatsSection.reset(new Widget("sec_stat", nullptr, { 0 ,0, 200, 20 }, true));
    m_secStatsSection->setTextStyle({ Font::latoRegular, FontSize::medium, Color::silver, width });
    m_descrSection.reset(new Widget("desc", nullptr, { 0 ,0, 200, 20 }, true));
    m_descrSection->setTextStyle({ Font::latoRegular, FontSize::medium, Color::silver, width });
    return true;
}

void ItemHelper::setItem(const Item& item)
{
    m_titleSection->setText(item.getName());
    m_descrSection->setText(item.getDesc());
    m_infoSection->setText(item.getClass() + ", " + item.getType());
    
    itemHasDescription = true;
    itemHasSecondary = false;

    initPrimaryStatsSection(item);
}

void ItemHelper::render(RenderSubsystem& rendSubsystem, 
                        ResourceSystem& resSystem,
                        Vec2i coordStart) const
{
    int x, y;
    SDL_GetMouseState(&x, &y);

    std::string iclass = "delete";
    std::string strdamage = "delete";

    Vec2i pos(x - s_width, y - 65);

    auto height = s_tMargin;
    height += m_titleSection->getHeight() + s_spacing;
    height += m_infoSection->getHeight() + s_spacing;
    height += itemHasPrimary ? m_primStatsSection->getHeight() + s_spacing : 0;
    height += itemHasSecondary ? m_secStatsSection->getHeight() + s_spacing : 0;
    height += itemHasDescription ? m_descrSection->getHeight() + s_spacing : 0;
    height += s_bMargin;

    auto texture = resSystem.get<Renderable>("helper_back");
    SDL_Rect dst = { pos.x, pos.y, s_width, height };
    rendSubsystem.render(texture, dst);

    int curHeight = s_tMargin;

    m_titleSection->setPosition({ s_lMargin, curHeight });
    m_titleSection->render(rendSubsystem, resSystem, pos);
    curHeight += m_titleSection->getHeight() + s_spacing;

    m_infoSection->setPosition({ s_lMargin, curHeight });
    m_infoSection->render(rendSubsystem, resSystem, pos);
    curHeight += m_infoSection->getHeight() + s_spacing;

    if (itemHasPrimary)
    {
        m_primStatsSection->setPosition({ s_lMargin, curHeight });
        m_primStatsSection->render(rendSubsystem, resSystem, pos);
        curHeight += m_primStatsSection->getHeight() + s_spacing;
    }

    m_descrSection->setPosition({ s_lMargin, curHeight });
    m_descrSection->render(rendSubsystem, resSystem, pos);
}

void ItemHelper::initPrimaryStatsSection(const Item& item)
{
    std::string primaryStats;
    int primaryStatsNum = 0;
    if (item.isWeapon())
    {
        auto& mdfrs = item.getMdfrs();
        for (auto& dmgType : Modifiers::dmgTypes)
        {
            if (mdfrs.weak_at(dmgType) > 0)
            {
                primaryStats += std::to_string(mdfrs.weak_at(dmgType))
                    + std::string(" ") + TextManager::instance().getPhrase(dmgType) + "\n";
                ++primaryStatsNum;
            }
        }
        m_primStatsSection->setText(primaryStats);
        m_primStatsSection->resize(m_primStatsSection->getWidth(), primaryStatsNum * 20);
        itemHasPrimary = true;
    }
    else if (item.isArmour())
    {
        auto& mdfrs = item.getMdfrs();
        for (auto& armType : Modifiers::armTypes)
        {
            if (mdfrs.weak_at(armType) > 0)
            {
                primaryStats += std::to_string(mdfrs.weak_at(armType))
                    + std::string(" ") + TextManager::instance().getPhrase(armType) + "\n";
                ++primaryStatsNum;
            }
        }
        m_primStatsSection->setText(primaryStats);
        m_primStatsSection->resize(m_primStatsSection->getWidth(), primaryStatsNum * 20);
        itemHasPrimary = true;
    }
    else
    {
        m_primStatsSection->setText("");
        itemHasPrimary = false;
    }
}

} /* gui namespace */