#include "gui_elem__hero_widget.h"

#include "renderable.h"
#include "atexture.h"
#include "widget__number.h"
#include "player_controller.h"
#include "system__resource.h"
#include "game_system_manager.h"
#include "text_renderer.h"
#include "font_data.h"
#include "color.h"

#include "component__attr.h"
#include "component__mdfr.h"

namespace gui {

void HeroPanel::init(ResourceSystem& resSystem, Actor& hero)
{
    auto texture = resSystem.get<Renderable>("hero_test_portrait_texture");
    auto widget = new Widget("portrait", this, { 20, 20, texture->getTexture()->getWidth(), texture->getTexture()->getHeight() }, true, texture);
    addChild("pan_mn", *widget);
    std::string fName = Font::latoRegular;
    int fSize = FontSize::medium;
    auto fColor = Color::silver;

    auto& attrs = hero.getComponent<AttrComponent>()->get();
    auto& mdfrs = hero.getComponent<MdfrComponent>()->get();

    texture = resSystem.textRenderer->renderTexture(hero.getRes(), fName, fSize, fColor);
    widget = new Widget("name", this, 35, 90, true, texture);
    addChild(*widget);

    texture = resSystem.textRenderer->renderTexture("Strength", fName, fSize, fColor);
    widget = new Widget("str", this, 20, 120, true, texture);
    addChild(*widget);

    texture = resSystem.textRenderer->renderTexture("Dexterity", fName, fSize, fColor);
    widget = new Widget("dex", this, 20, 140, true, texture);
    addChild(*widget);

    texture = resSystem.textRenderer->renderTexture("Intelligence", fName, fSize, fColor);
    widget = new Widget("int", this, 20, 160, true, texture);
    addChild(*widget);

    texture = resSystem.textRenderer->renderTexture("Vitality", fName, fSize, fColor);
    widget = new Widget("vit", this, 20, 180, true, texture);
    addChild(*widget);

    texture = resSystem.textRenderer->renderTexture("Charisma", fName, fSize, fColor);
    widget = new Widget("chr", this, 20, 200, true, texture);
    addChild(*widget);

    texture = resSystem.textRenderer->renderTexture("Perception", fName, fSize, fColor);
    widget = new Widget("per", this, 20, 220, true, texture);
    addChild(*widget);

    widget = new NumberWidget("str_n", this, { 140, 120, 0, 0 }, true, &attrs.at(Attr("str")));
    addChild(*widget);

    widget = new NumberWidget("dex_n", this, { 140, 140, 0, 0 }, true, &attrs.at(Attr("dex")));
    addChild(*widget);

    widget = new NumberWidget("int_n", this, { 140, 160, 0, 0 }, true, &attrs.at(Attr("int")));
    addChild(*widget);

    widget = new NumberWidget("vit_n", this, { 140, 180, 0, 0 }, true, &attrs.at(Attr("vit")));
    addChild(*widget);

    widget = new NumberWidget("chr_n", this, { 140, 200, 0, 0 }, true, &attrs.at(Attr("chr")));
    addChild(*widget);

    widget = new NumberWidget("per_n", this, { 140, 220, 0, 0 }, true, &attrs.at(Attr("per")));
    addChild(*widget);

    texture = resSystem.textRenderer->renderTexture("Damage", fName, fSize, fColor);
    addChild(*new Widget("dmg", this, 200, 120, true, texture));

    texture = resSystem.get<Renderable>("ph_dmg");
    addChild(*new Widget("dmg_ph_icon", this, 200, 140, true, texture));

    widget = new NumberWidget("dmg_ph_n", this, { 220, 140, 0, 0 }, true, &mdfrs.at("dmg_ph"));
    addChild(*widget);

    texture = resSystem.get<Renderable>("m_dmg");
    addChild(*new Widget("dmg_m_icon", this, 200, 160, true, texture));

    widget = new NumberWidget("dmg_m_n", this, { 220, 160, 0, 0 }, true, &mdfrs.at("dmg_mgc"));
    addChild(*widget);

    texture = resSystem.get<Renderable>("f_dmg");
    addChild(*new Widget("dmg_f_icon", this, 240, 140, true, texture));

    widget = new NumberWidget("dmg_f_n", this, { 260, 140, 0, 0 }, true, &mdfrs.at("dmg_fr"));
    addChild(*widget);

    texture = resSystem.get<Renderable>("fr_dmg");
    addChild(*new Widget("dmg_fr_icon", this, 240, 160, true, texture));

    widget = new NumberWidget("dmg_fr_n", this, { 260, 160, 0, 0 }, true, &mdfrs.at("dmg_frz"));
    addChild(*widget);

    texture = resSystem.get<Renderable>("l_dmg");
    addChild(*new Widget("dmg_l_icon", this, 280, 140, true, texture));

    widget = new NumberWidget("dmg_l_n", this, { 300, 140, 0, 0 }, true, &mdfrs.at("dmg_lig"));
    addChild(*widget);

    texture = resSystem.get<Renderable>("p_dmg");
    addChild(*new Widget("dmg_p_icon", this, 280, 160, true, texture));

    widget = new NumberWidget("dmg_p_n", this, { 300, 160, 0, 0 }, true, &mdfrs.at("dmg_psn"));
    addChild(*widget);

    texture = resSystem.get<Renderable>("ch_dmg");
    addChild(*new Widget("dmg_ch_icon", this, 320, 140, true, texture));

    widget = new NumberWidget("dmg_ch_n", this, { 340, 140, 0, 0 }, true, &mdfrs.at("dmg_ch"));
    addChild(*widget);

    texture = resSystem.textRenderer->renderTexture("Resistance", fName, fSize, fColor);
    addChild(*new Widget("res", this, 200, 180, true, texture));

    texture = resSystem.get<Renderable>("ph_dmg");
    addChild(*new Widget("res_ph_icon", this, 200, 200, true, texture));

    widget = new NumberWidget("res_ph_n", this, { 220, 200, 0, 0 }, true, &mdfrs.at("res_ph"));
    addChild(*widget);

    texture = resSystem.get<Renderable>("m_dmg");
    addChild(*new Widget("res_m_icon", this, 200, 220, true, texture));

    widget = new NumberWidget("res_m_n", this, { 220, 220, 0, 0 }, true, &mdfrs.at("res_mgc"));
    addChild(*widget);

    texture = resSystem.get<Renderable>("f_dmg");
    addChild(*new Widget("res_f_icon", this, 240, 200, true, texture));

    widget = new NumberWidget("res_f_n", this, { 260, 200, 0, 0 }, true, &mdfrs.at("res_fr"));
    addChild(*widget);

    texture = resSystem.get<Renderable>("fr_dmg");
    addChild(*new Widget("res_fr_icon", this, 240, 220, true, texture));

    widget = new NumberWidget("res_fr_n", this, { 260, 220, 0, 0 }, true, &mdfrs.at("res_frz"));
    addChild(*widget);

    texture = resSystem.get<Renderable>("l_dmg");
    addChild(*new Widget("res_l_icon", this, 280, 200, true, texture));

    widget = new NumberWidget("res_l_n", this, { 300, 200, 0, 0 }, true, &mdfrs.at("res_lig"));
    addChild(*widget);

    texture = resSystem.get<Renderable>("p_dmg");
    addChild(*new Widget("res_p_icon", this, 280, 220, true, texture));

    widget = new NumberWidget("res_p_n", this, { 300, 220, 0, 0 }, true, &mdfrs.at("res_psn"));
    addChild(*widget);

    texture = resSystem.get<Renderable>("ch_dmg");
    addChild(*new Widget("res_ch_icon", this, 320, 200, true, texture));

    widget = new NumberWidget("res_ch_n", this, { 340, 200, 0, 0 }, true, &mdfrs.at("res_ch"));
    addChild(*widget);

    texture = resSystem.textRenderer->renderTexture("Armor", fName, fSize, fColor);
    addChild(*new Widget("arm", this, 200, 240, true, texture));

    texture = resSystem.get<Renderable>("ph_dmg");
    addChild(*new Widget("arm_ph_icon", this, 200, 260, true, texture));

    widget = new NumberWidget("arm_ph_n", this, { 220, 260, 0, 0 }, true, &mdfrs.at("arm_ph"));
    addChild(*widget);

    texture = resSystem.get<Renderable>("m_dmg");
    addChild(*new Widget("arm_m_icon", this, 240, 260, true, texture));

    widget = new NumberWidget("arm_m_n", this, { 260, 260, 0, 0 }, true, &mdfrs.at("arm_mgc"));
    addChild(*widget);
}

HeroPanel::HeroPanel(const std::string& name,
                     Widget* parent,
                     int x,
                     int y,
                     int width,
                     int height,
                     bool visible,
                     Renderable* backImage) :
    Widget(name, parent, { x, y, width, height }, visible, backImage)
{}

} /* gui namespace. */