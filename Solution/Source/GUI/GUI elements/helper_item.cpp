#include "helper_item.h"

#include <string>
#include <vector>

#include "item.h"
#include "slot__item.h"
#include "modifiers.h"
#include "system__resource.h"
#include "subsystem__render.h"
#include "text_renderer.h"
#include "font_data.h"
#include "color.h"

#include "widget__text_holder.h"
#include "text_manager.h"

namespace gui {

ItemHelper::ItemHelper() :
    Widget(nullptr)
{
    init();
}

bool ItemHelper::init()
{
    m_titleSection.reset(new TextOwnerWidget("title", nullptr, { 0 ,0, 200, 20 }, true, {Font::latoBold, FontSize::large, Color::silver}));
    m_infoSection.reset(new TextOwnerWidget("itype", nullptr, { 0, 0, 200, 20 }, true, { Font::latoRegular, FontSize::medium, Color::silver }));
    m_primStatsSection.reset(new TextOwnerWidget("prim_stat", nullptr, { 0 ,0, 200, 20 }, true, { Font::latoBold, FontSize::medium, Color::silver }));
    m_secStatsSection.reset(new TextOwnerWidget("sec_stat", nullptr, { 0 ,0, 200, 20 }, true, { Font::latoRegular, FontSize::medium, Color::silver }));
    m_descrSection.reset(new TextOwnerWidget("desc", nullptr, { 0 ,0, 200, 20 }, true, { Font::latoRegular, FontSize::medium, Color::silver }));
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

void ItemHelper::render(RenderSubsystem& rendSubsys, ResourceSystem& resSystem) const
{
    int x, y;
    SDL_GetMouseState(&x, &y);

    std::string iclass = "delete";
    std::string strdamage = "delete";

    Vec2i pos(x - width, y - 65);

    auto height = tMargin;
    height += m_titleSection->getHeight() + spacing;
    height += m_infoSection->getHeight() + spacing;
    height += itemHasPrimary ? m_primStatsSection->getHeight() + spacing : 0;
    height += itemHasSecondary ? m_secStatsSection->getHeight() + spacing : 0;
    height += itemHasDescription ? m_descrSection->getHeight() + spacing : 0;
    height += bMargin;

    auto texture = resSystem.get<Renderable>("helper_back");
    SDL_Rect dst = { pos.x, pos.y, width, height };
    rendSubsys.render(texture, dst);

    int curHeight = tMargin;

    m_titleSection->setPosition({ lMargin, curHeight });
    m_titleSection->render(rendSubsys, resSystem, pos);
    curHeight += m_titleSection->getHeight() + spacing;

    m_infoSection->setPosition({ lMargin, curHeight });
    m_infoSection->render(rendSubsys, resSystem, pos);
    curHeight += m_infoSection->getHeight() + spacing;

    m_primStatsSection->setPosition({ lMargin, curHeight });
    m_primStatsSection->render(rendSubsys, resSystem, pos);
    curHeight += m_primStatsSection->getHeight() + spacing;

    m_descrSection->setPosition({ lMargin, curHeight });
    m_descrSection->render(rendSubsys, resSystem, pos);
}

ItemHelper::~ItemHelper() = default;

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