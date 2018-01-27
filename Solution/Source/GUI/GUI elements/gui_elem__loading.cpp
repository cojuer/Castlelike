#include "gui_elem__loading.h"

#include <iostream>

#include "system__resource.h"
#include "system__save.h"

#include "widget__dropdown_list.h"
#include "widget__text.h"

#include "font_data.h"
#include "atexture.h"
#include "spritesheet.h"
#include "text_renderer.h"
#include "event__load.h"
#include "on_release.h"
#include "event__menu.h"

namespace gui {

LoadingWidget::LoadingWidget(Widget* parent) :
    Widget(parent), 
    m_resSystem(nullptr),
    m_saveSystem(nullptr),
    m_profMenu(nullptr)
{}

LoadingWidget::LoadingWidget(const std::string& name,
                             Widget* parent,
                             SDL_Rect rect,
                             bool visible,
                             Renderable* rendered) :
    Widget(name, parent, rect, visible, rendered),
    m_resSystem(nullptr),
    m_saveSystem(nullptr),
    m_profMenu(nullptr)
{}

void LoadingWidget::init(ResourceSystem& resSystem, SaveSystem& saveSystem)
{
    m_resSystem = &resSystem;
    m_saveSystem = &saveSystem;
    
    // FIXME: magic consts
    auto profiles = m_saveSystem->getProfiles();
    auto profW = 100;
    auto profH = 40;
    auto profMenuX = (getWidth() - profW) / 2;
    auto profMenuY = (60 - profH) / 2;
    m_profMenu = new DropDownList{ "profiles", nullptr, { profMenuX, profMenuY, profW, profH }, true };
    for (auto& profile : profiles)
    {
        m_profMenu->addElem(profile, resSystem);
    }
    addChild(*m_profMenu);

    refresh();
}

bool LoadingWidget::handle(SDL_Event& event, Vec2i coordStart)
{
    if (!m_visible) return false;

    coordStart += getPos();
    m_profMenu->handle(event, coordStart);
    if (m_profMenu->getActiveElem() != m_saveSystem->getCurrProfile())
    {
        m_saveSystem->useProfile(m_profMenu->getActiveElem());
        refresh();
    }

    for (auto&[save, button] : m_saveButtons)
    {
        button->handle(event, coordStart);
    }

    return true;
}

void LoadingWidget::refresh()
{
    for (auto&[name, button] : m_saveButtons)
    {
        m_children.erase(name);
    }
    m_saveButtons.clear();

    auto currProf = m_saveSystem->getCurrProfile();
    m_profMenu->setActiveElem(currProf);
    auto saves = m_saveSystem->getSaves(currProf);
    auto offset = 75;
    for (auto& save : saves)
    {
        // FIXME: memory leak, renderer requires possibility to give spritesheets
        auto sprites = new SprSheet{
            std::vector<ATexture*>{
                m_resSystem->textRenderer->renderTexture(save.name, Font::latoBold, FontSize::medium, Color::silver),
                m_resSystem->textRenderer->renderTexture(save.name, Font::latoBold, FontSize::medium, Color::silver),
                m_resSystem->textRenderer->renderTexture(save.name, Font::latoBold, FontSize::medium, Color::silver),
                m_resSystem->textRenderer->renderTexture(save.name, Font::latoBold, FontSize::medium, Color::silver),
                m_resSystem->textRenderer->renderTexture(save.name, Font::latoBold, FontSize::medium, Color::silver)
            }
        };
        auto loadEvent = new LoadEvent{ currProf, save.name };
        auto menuEvent = new MenuEvent{ MenuState::ON_LOAD };
        auto button = new Button{ save.name, this, { 20, offset, 20, 100 }, true, sprites, nullptr };
        button->setBhvr({ new OnRelease{ loadEvent }, new OnRelease{ menuEvent } });
        addChild(*button);
        m_saveButtons[save.name] = button;
        offset += 70;
    }
}

} /* gui namespace. */
