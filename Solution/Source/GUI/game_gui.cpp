#include "game_gui.h"

#include "subsystem__event.h"
#include "subsystem__render.h"
#include "game_system_manager.h"
#include "system__dialogue.h"
#include "system__resource.h"
#include "system__scene.h"

#include "global_time.h"
#include "utils.h"
#include "font_data.h"
#include "event__dialogue.h"
#include "text_renderer.h"
#include "listener__gui.h"

#include "widget__button.h"
#include "widget__progress_bar.h"
#include "widget__text.h"
#include "slot_helper.h"
#include "slot__item.h"
#include "gui_elem__bag_widget.h"
#include "gui_elem__equip_widget.h"
#include "gui_elem__action_panel.h"
#include "gui_elem__hero_widget.h"

#include "component__action_pts.h"
#include "component__bag.h"
#include "component__equipment.h"
#include "component__experience_interface.h"
#include "component__health.h"
#include "component__reactor_interface.h"
#include "component__stamina.h"

namespace gui {
    
GameGUI::GameGUI() = default;

bool GameGUI::init(Options& opts,
                   RenderSubsystem& rendSubsystem,
                   GameSystemManager&    sysManager,
                   SceneSystem&     sceneSystem,
                   ResourceSystem&  resSystem)
{
    m_opts = &opts;
    m_state = GameGUIState::NORMAL;

    m_hero = sceneSystem.getScene()->getHero();
    assert(m_hero && "hero not available");

    // FIXME: do we need journal?
    m_journal = resSystem.m_journal;
    m_rendSubsystem = &rendSubsystem;
    m_resSystem = &resSystem;
    m_sysManager = &sysManager;
    m_sceneSystem = &sceneSystem;

    m_listener.reset(new GUIListener(*this));
    m_reg.reset(EventSubsystem::AddHandler(*m_listener));

    m_textBufferBack = std::make_unique<Widget>(
        std::string("journal_back"), 
        nullptr, 
        SDL_Rect{ 0, 0, 300, 150 }, 
        true, 
        m_resSystem->get<Renderable>("text_buffer_back")
    );

    m_slotHelper = std::make_unique<SlotHelper>();

    m_dialWdg = std::make_unique<Widget>(
        std::string("dial_wdg"), 
        nullptr, 
        SDL_Rect{ 0, 500, m_opts->getInt("Width"), 160 }, 
        false, 
        m_resSystem->get<Renderable>("hero_panel_back_texture")
    );

    //! init status check
    initHeroBars();
    initHeroPanel();
    initInventory();
    initBagWidget();
    initActionsWdg();
    initDlMenu();

    return (m_journal != nullptr);
}

void GameGUI::initHeroBars()
{
    m_hpWdg = std::unique_ptr<Widget>(m_resSystem->get<Widget>("hp_bar"));
    auto progBarHpWdg = dcast<ProgressBar*>(m_hpWdg.get());
    auto hpComponent = m_hero->getComponent<HealthComponent>();
    progBarHpWdg->setData(hpComponent->getCurr(), hpComponent->getMax());
    m_widgets.push_back(m_hpWdg.get());

    m_spWdg = std::unique_ptr<Widget>(m_resSystem->get<Widget>("sp_bar"));
    auto progBarSpWdg = dcast<ProgressBar*>(m_spWdg.get());
    auto spComponent = m_hero->getComponent<StaminaComponent>();
    progBarSpWdg->setData(spComponent->getCurr(), spComponent->getMax());
    m_widgets.push_back(m_spWdg.get());

    m_xpWdg = std::unique_ptr<Widget>(m_resSystem->get<Widget>("xp_bar"));
    auto barWdg = dcast<ProgressBar*>(m_xpWdg.get());
    auto xpComponent = m_hero->getComponent<ExperienceInterfaceComponent>();
    barWdg->setData(xpComponent->getXp(), xpComponent->getXpToLvlUp());
    m_widgets.push_back(m_xpWdg.get());
}

void GameGUI::initHeroPanel()
{
    auto texture = m_resSystem->get<Renderable>("hero_panel_back_texture");
    auto panel = new HeroPanel("hero_panel", nullptr, 100, 100, 400, 400, false, texture);
    panel->init(*m_resSystem, *m_hero);
    m_heroWdg = std::unique_ptr<Widget>(panel);
    m_widgets.push_back(m_heroWdg.get());
}

void GameGUI::initInventory()
{
    auto& equipment = m_hero->getComponent<EquipmentComponent>()->get();
    m_equipWdg = dcast<EquipmentWidget*>(m_resSystem->get<Widget>("equipment"));
    m_equipWdg->setEquipment(equipment);

    auto& bag = m_hero->getComponent<BagComponent>()->get();
    m_bagWdg = dcast<BagWidget*>(m_resSystem->get<Widget>("bag"));
    m_bagWdg->setContainer(&bag);

    m_inventoryWdg = std::unique_ptr<Widget>(m_resSystem->get<Widget>("inventory"));
    m_inventoryWdg->setVisible(false);
    m_inventoryWdg->addChild(*m_equipWdg);
    m_inventoryWdg->addChild(*m_bagWdg);

    m_widgets.push_back(m_inventoryWdg.get());
}

void GameGUI::initBagWidget()
{
    m_lootWdg = std::unique_ptr<BagWidget>(dcast<BagWidget*>(m_resSystem->get<Widget>("secbag")));
    m_lootWdg->setVisible(false);
    m_widgets.push_back(m_lootWdg.get());
}

void GameGUI::initActionsWdg()
{
    m_actionsWdg = std::unique_ptr<ActPanel>(dcast<ActPanel*>(m_resSystem->get<Widget>("actpanel")));
    // TEST
    auto& slots = m_actionsWdg->getSlots();
    slots[0].setAction("action_move", *m_resSystem);
    slots[1].setAction("action_attack", *m_resSystem);
    slots[2].setAction("action_discard", *m_resSystem);
    slots[3].setAction("action_whirlwind", *m_resSystem);
    slots[4].setAction("action_swing", *m_resSystem);
    slots[5].setAction("action_mighty_blow", *m_resSystem);
    // TEST
    m_widgets.push_back(m_actionsWdg.get());
}

// FIXME: rewrite
void GameGUI::initDlMenu()
{
    //dialWdg->setTrigger(new ButtonTrigger(dialWdg, new DlEvent(DlEvType::NEXT_PHRASE)));

    const int tMarg = 20;
    const int lMarg = 20;

    const std::string& text = m_resSystem->dialogueManager->getCurText();
    Widget* textPanel = new TextWidget("text", m_dialWdg.get(), { lMarg, tMarg, m_opts->getInt("Width"), 100 }, true, Font::latoRegular, FontSize::medium, Color::silver, &text);

    int height = tMarg + 2 * FontSize::medium;
    for (int i = 0; i < dialMaxAnswers; ++i)
    {
        Widget* answer = new Button(std::string("answer ") + std::to_string(i),
            m_dialWdg.get(), { lMarg, height }, true, nullptr, new DlEvent(DlEvType::CHOOSE_ANSWER, i));
        m_dialWdg->addChild(*answer);
        height += FontSize::medium;
    }

    m_dialWdg->addChild("text", *textPanel);

    m_widgets.push_back(m_dialWdg.get());
}

void GameGUI::handle(SDL_Event& event)
{
    switch(m_state)
    {
    case GameGUIState::NORMAL:
        handleStateNormal(event);
        break;
    case GameGUIState::ACTION_INPUT:
        handleStateActInput(event);
        break;
    case GameGUIState::ACTION_ANIM:
        handleStateActAnim(event);
        break;
    case GameGUIState::CUTSCENE:
        handleStateCutscene(event);
        break;
    default:
        break;
    }
}

void GameGUI::handleDialogue(SDL_Event& event)
{
    if (!m_dialWdg->isVisible()) return;
    
    auto& dlMgr = *m_resSystem->dialogueManager;
    if (dlMgr.getPhrase() == dlMgr.getCurState()->phrases.size() - 1 &&
        dlMgr.getCurPhrase()->nextState != -1)
    {
        m_dialWdg->setState(WState::INACTIVE);
    }
    else if (m_dialWdg->getState() == WState::INACTIVE)
    {
        m_dialWdg->setState(WState::MOUSE_OUT);
    }
    m_dialWdg->handle(event);
}

GameGUI::~GameGUI()
{
    m_reg->removeHandler();
}

void GameGUI::handleInventory(SDL_Event& event)
{
    auto& bag = m_hero->getComponent<BagComponent>()->get();
    auto loot = m_lootWdg->getContainer();
    auto equip = m_equipWdg->getEquipment();

    m_currentSlot = nullptr;
    updateCurSlot();
    m_slotHelper->setSlot(m_currentSlot);

    Vec2i coordStart = { 0, 0 };
    if (!m_activeSlot && m_currentSlot)
    {
        coordStart = m_currentSlot->getCoordStart();
        if (!m_currentSlot->isEmpty() && m_currentSlot->handle(event, coordStart))
        {
            std::swap(m_activeSlot, m_currentSlot);
            std::swap(m_activeSlotType, m_currentSlotType);
            std::swap(m_activeSlotIndex, m_currentSlotIndex);
        }
    }

    auto moved = false;
    if (m_activeSlot &&
        m_activeSlot->handle(event, coordStart) == false)
    {
        if (m_currentSlot)
        {
            moved = moved || tryMoveBagToBag(bag, event);
            moved = moved || tryMoveBagToEquip(bag, *equip, event);
            moved = moved || tryMoveLootToLoot(*loot, event);
            moved = moved || tryMoveLootToEquip(*loot, bag, *equip, event);
            moved = moved || tryMoveEquipToEquip(bag, event);
        }
        moved = moved || tryMoveBagToLoot(bag, *loot, event);
        moved = moved || tryMoveLootToBag(*loot, bag, event);
        moved = moved || tryMoveEquipToBag(bag, event);
        moved = moved || tryMoveEquipToLoot(*loot, event);
        
        m_activeSlot = nullptr;
    }

    if (m_currentSlot)
    {
        moved = moved || tryFastMoveLootToBag(*loot, bag, event);
        moved = moved || tryFastMoveBagToEquip(bag, *equip, event);
        moved = moved || tryFastMoveEquipToBag(*equip, bag, event);
    }

    if (moved)
    {
        m_bagWdg->refresh();
        m_lootWdg->refresh();
        m_equipWdg->refresh();
    }
}

void GameGUI::handleKeyboard(SDL_Event& event)
{
    auto curr = event.key.keysym.sym;
    if (curr == m_opts->getInt("open_hero_panel"))
    {
        m_heroWdg->setVisible(!m_heroWdg->isVisible());
    }
    else if (curr == m_opts->getInt("open_equip"))
    {
        m_inventoryWdg->setVisible(!m_inventoryWdg->isVisible());
    }
    else if (curr == m_opts->getInt("open_skills"))
    {
        m_actionsWdg->setVisible(!m_actionsWdg->isVisible());
    }
    else if (curr == SDLK_SPACE)
    {
        auto& gTime = GlobalTime::instance();
        if (gTime.isPaused())
        {
            gTime.unpause();
        }
        else
        {
            gTime.pause();
        }
    }
    int access_flag = -1;
    if (curr == m_opts->getInt("quick_access_1"))      access_flag = 0;
    else if (curr == m_opts->getInt("quick_access_2")) access_flag = 1;
    else if (curr == m_opts->getInt("quick_access_3")) access_flag = 2;
    else if (curr == m_opts->getInt("quick_access_4")) access_flag = 3;
    else if (curr == m_opts->getInt("quick_access_5")) access_flag = 4;
    else if (curr == m_opts->getInt("quick_access_6")) access_flag = 5;
    // Check if it is right turn
    
    auto actionPtsComp = m_hero->getComponent<ActionPtsComponent>();
    if (actionPtsComp &&
        actionPtsComp->getCurr() > 0 &&
        access_flag != -1)
    {
        auto& slots = m_actionsWdg->getSlots();
        if (!slots[access_flag].isEmpty())
        {
            auto& scene = *m_sceneSystem->getScene();
            ActionArgs input;
            input[ActArgType::user] = m_hero;
            input[ActArgType::scene] = &scene;
            m_action = m_resSystem->actionManager->getAction(slots[access_flag].getAction(), std::move(input));
            m_state = GameGUIState::ACTION_INPUT;
        }
    }
}

// FIXME: function too large
void GameGUI::handleStateNormal(SDL_Event& event)
{
    int x, y;
    SDL_GetMouseState(&x, &y);

    auto& scene = *m_sceneSystem->getScene();

    if (event.type == SDL_KEYDOWN)
    {
        handleKeyboard(event);
    }

    /* Open container within range 1 from hero. */
    if (!this->isPointOnGUI({ x, y }) &&
        event.type == SDL_MOUSEBUTTONDOWN &&
        event.button.button == SDL_BUTTON_LEFT)
    {
        auto viewport = m_sysManager->m_viewSystem->getCamera().getViewport();
        auto center = m_sysManager->m_viewSystem->getCamera().getCenter();
        x = center.x + std::round((x - viewport.x - viewport.w / 2 - 32) / 64.);
        y = center.y + std::round((y - viewport.y - viewport.h / 2 - 32) / 64.);
        auto contActor = scene.getActor({ x, y }, ActorType::CONTAINER);
        if (utils::coordDist({ x, y }, m_hero->getCoord()) <= 1 && contActor)
        {
            auto& container = contActor->getComponent<BagComponent>()->get();
            m_lootWdg->setContainer(&container);
            m_lootWdg->setVisible(true);
        }
		auto actors = scene.getActorsAtCoord({ x, y });
		for (auto& actor : actors)
		{
			auto component = actor->getComponent<ReactorComponentInterface>();
			if (component)
            {
                component->react("on_use", { {ActArgType::scene, &scene } });
			}
		}
    }

    handleInventory(event);
    handleDialogue(event);

    auto& slots = m_actionsWdg->getSlots();
    auto coord = m_actionsWdg->getPos();
    for (auto& slot: slots)
    {
        if (slot.handle(event, coord) &&
            !slot.isEmpty())
        {
            ActionArgs input;
            input[ActArgType::user] = m_hero;
            input[ActArgType::scene] = &scene;
            m_action = m_resSystem->actionManager->getAction(slot.getAction(), std::move(input));
            m_state = GameGUIState::ACTION_INPUT;
        }
    }
}

void GameGUI::handleStateActInput(SDL_Event& event)
{
    int x, y;
    SDL_GetMouseState(&x, &y);

    if (!this->isPointOnGUI({ x, y })
        and event.type == SDL_MOUSEBUTTONDOWN
        and event.button.button == SDL_BUTTON_LEFT)
    {
        // FIXME: stop using magic consts
        auto viewport = m_sysManager->m_viewSystem->getCamera().getViewport();
        auto center = m_sysManager->m_viewSystem->getCamera().getCenter();
        x = center.x + std::round((x - viewport.x - viewport.w / 2 - 32) / 64.);
        y = center.y + std::round((y - viewport.y - viewport.h / 2 - 32) / 64.);
        m_action->setArg(ActArgType::coord, new Coord(x, y));
        m_action->act();
        delete(m_action);
        m_action = nullptr;
        m_state = GameGUIState::NORMAL;
    }
}

void GameGUI::handleStateActAnim(SDL_Event& event)
{
}

void GameGUI::handleStateCutscene(SDL_Event& event)
{
}

void GameGUI::updateCurSlot()
{
    int x, y;
    SDL_GetMouseState(&x, &y);

    if (m_inventoryWdg->isVisible() &&
        m_bagWdg->isPointOn({ x, y }, m_inventoryWdg->getPos()))
    {
        auto coordStart = m_bagWdg->getPos() + m_inventoryWdg->getPos();
        updateCurSlot(m_bagWdg->getSlots(), ActSlotType::BAG, coordStart);
    }
    if (m_lootWdg->isPointOn({ x, y }))
    {
        updateCurSlot(m_lootWdg->getSlots(), ActSlotType::LOOT, m_lootWdg->getPos());
    }
    if (m_inventoryWdg->isVisible() &&
        m_equipWdg->isPointOn({ x, y }, m_inventoryWdg->getPos()))
    {
        auto coordStart = m_equipWdg->getPos() + m_inventoryWdg->getPos();
        updateCurSlot(m_equipWdg->getSlots(), ActSlotType::EQUIP, coordStart);
    }
}

bool GameGUI::tryMoveBagToBag(Container& bag, SDL_Event& event) const
{
    if (m_activeSlotType == ActSlotType::BAG && 
        m_currentSlotType == ActSlotType::BAG && 
        m_currentSlotIndex != m_activeSlotIndex)
    {
        bag.swapSlots(m_activeSlotIndex, m_currentSlotIndex);
        return true;
    }
    return false;
}

bool GameGUI::tryMoveBagToLoot(Container& bag, Container& loot, SDL_Event& event) const
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    if (m_activeSlotType == ActSlotType::BAG &&
        m_lootWdg->isPointOn({ x, y }) &&
        loot.add(*m_activeSlot->getItem()))
    {
        bag.eraseSlot(m_activeSlotIndex);
        return true;
    }
    return false;
}

bool GameGUI::tryMoveBagToEquip(Container& bag, Equipment& equip, SDL_Event& event) const
{
    if (m_activeSlotType == ActSlotType::BAG &&
        m_currentSlotType == ActSlotType::EQUIP &&
        m_equipWdg->canEquip(m_currentSlotIndex, *m_activeSlot->getItem()))
    {
        if (m_equipWdg->isEquipped(m_currentSlotIndex))
        {
            auto item = m_activeSlot->getItem();
            bag.eraseSlot(m_activeSlotIndex);
            bag.add(*m_currentSlot->getItem());
            m_equipWdg->equip(m_currentSlotIndex, *item);
            EventSubsystem::FireEvent(*new ActorEvent(ActorEvType::ITEM_EQUIPPED, m_hero->getID()));
        }
        else
        {
            m_equipWdg->equip(m_currentSlotIndex, *m_activeSlot->getItem());
            bag.eraseSlot(m_activeSlotIndex);
            EventSubsystem::FireEvent(*new ActorEvent(ActorEvType::ITEM_EQUIPPED, m_hero->getID()));
        }
        return true;
    }
    return false;
}

bool GameGUI::tryMoveLootToBag(Container& loot, Container& bag, SDL_Event& event) const
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    if (m_activeSlotType == ActSlotType::LOOT &&
        m_bagWdg->isPointOn({ x, y }, m_inventoryWdg->getPos()) &&
        bag.add(*m_activeSlot->getItem()))
    {
        loot.eraseSlot(m_activeSlotIndex);
        if (loot.isEmpty())
        {
            m_lootWdg->setVisible(false);
        }
        return true;
    }
    return false;
}

bool GameGUI::tryMoveLootToLoot(Container& loot, SDL_Event& event) const
{
    if (m_activeSlotType == ActSlotType::LOOT 
        and m_currentSlotType == ActSlotType::LOOT
        and m_activeSlotIndex != m_currentSlotIndex)
    {
        loot.swapSlots(m_activeSlotIndex, m_currentSlotIndex);
        return true;
    }
    return false;
}

bool GameGUI::tryMoveLootToEquip(Container& loot, Container& bag, Equipment& equip, SDL_Event& event) const
{
    if (m_activeSlotType == ActSlotType::LOOT &&
        m_currentSlotType == ActSlotType::EQUIP &&
        m_equipWdg->canEquip(m_currentSlotIndex, *m_activeSlot->getItem()))
    {
        if (m_equipWdg->isEquipped(m_currentSlotIndex) &&
            !bag.isFull())
        {
            bag.add(*m_currentSlot->getItem());
            m_equipWdg->unequip(m_currentSlotIndex);
            m_equipWdg->equip(m_currentSlotIndex, *m_activeSlot->getItem());
            loot.eraseSlot(m_activeSlotIndex);
            // FIXME: update modifiers
            EventSubsystem::FireEvent(*new ActorEvent(ActorEvType::ITEM_EQUIPPED, m_hero->getID()));
            if (loot.isEmpty()) m_lootWdg->setVisible(false);
        }
        else if (!m_equipWdg->isEquipped(m_currentSlotIndex))
        {
            m_equipWdg->equip(m_currentSlotIndex, *m_activeSlot->getItem());
            loot.eraseSlot(m_activeSlotIndex);
            EventSubsystem::FireEvent(*new ActorEvent(ActorEvType::ITEM_EQUIPPED, m_hero->getID()));
            if (loot.isEmpty()) m_lootWdg->setVisible(false);
        }
        return true;
    }
    return false;
}

bool GameGUI::tryMoveEquipToBag(Container& bag, SDL_Event& event) const
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    if (m_activeSlotType == ActSlotType::EQUIP &&
        m_bagWdg->isPointOn({x, y}, m_inventoryWdg->getPos()) &&
        bag.add(*m_activeSlot->getItem()))
    {
        m_equipWdg->unequip(m_activeSlotIndex);
        EventSubsystem::FireEvent(*new ActorEvent(ActorEvType::ITEM_EQUIPPED, m_hero->getID()));
        return true;
    }
    return false;
}

bool GameGUI::tryMoveEquipToLoot(Container& loot, SDL_Event& event) const
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    if (m_activeSlotType == ActSlotType::EQUIP &&
        m_lootWdg->isPointOn({x, y}) &&
        loot.add(*m_activeSlot->getItem()))
    {
        m_equipWdg->unequip(m_activeSlotIndex);
        // FIXME: update modifiers
        return true;
    }
    return false;
}

bool GameGUI::tryMoveEquipToEquip(Container& bag, SDL_Event& event) const
{
    return false;
}

bool GameGUI::tryFastMoveLootToBag(Container& loot, Container& bag, SDL_Event& event) const
{
    if (event.type == SDL_MOUSEBUTTONDOWN &&
        event.button.button == SDL_BUTTON_RIGHT &&
        !m_currentSlot->isEmpty() &&
        m_currentSlotType == ActSlotType::LOOT &&
        bag.add(*m_currentSlot->getItem()))
    {
        loot.eraseSlot(m_currentSlotIndex);
        if (loot.isEmpty()) m_lootWdg->setVisible(false);
        return true;
    }
    return false;
}

bool GameGUI::tryFastMoveBagToEquip(Container& bag, Equipment& equip, SDL_Event& event) const
{
    // FIXME: to rework
    if (event.type == SDL_MOUSEBUTTONDOWN &&
        event.button.button == SDL_BUTTON_RIGHT &&
        !m_currentSlot->isEmpty() &&
        m_currentSlotType == ActSlotType::BAG &&
        equip.canEquip(*m_currentSlot->getItem()))
    {
        auto slotType = equip.slotFor(*m_currentSlot->getItem());
        auto equippedItem = equip.getItem(slotType);
        equip.equip(*m_currentSlot->getItem());
        bag.eraseSlot(m_currentSlotIndex);
        if (equippedItem)
        {
            bag.add(*equippedItem);
        }
        EventSubsystem::FireEvent(*new ActorEvent(ActorEvType::ITEM_EQUIPPED, m_hero->getID()));
        return true;
    }
    return false;
}

bool GameGUI::tryFastMoveEquipToBag(Equipment& equip, Container& bag, SDL_Event& event) const
{
    if (event.type == SDL_MOUSEBUTTONDOWN &&
        event.button.button == SDL_BUTTON_RIGHT &&
        !m_currentSlot->isEmpty() &&
        m_currentSlotType == ActSlotType::EQUIP &&
        bag.add(*m_currentSlot->getItem()))
    {
        m_equipWdg->unequip(m_currentSlotIndex);
        EventSubsystem::FireEvent(*new ActorEvent(ActorEvType::ITEM_EQUIPPED, m_hero->getID()));
        return true;
    }
    return false;
}

bool GameGUI::isPointOnGUI(Vec2i point) const
{
    auto pointOn = false;
    for (auto& widget : m_widgets)
    {
        pointOn = pointOn || widget->isPointOn(point);
    }
    return pointOn;
}

// FIXME: rewrite
void GameGUI::refreshDlMenu()
{
    const auto& dlMgr = *m_resSystem->dialogueManager;

    if (dlMgr.getState() == -1)
    {
        m_dialWdg->setVisible(false);
        for (auto i = 0; i < dialMaxAnswers; ++i)
        {
            auto widg = m_dialWdg->getChild(std::string("answer ") + std::to_string(i));
            auto butt = dcast<Button*>(widg);
            butt->setVisible(false);
        }
        return;
    }

    //if (dlMgr.getPhrase() == dlMgr.getCurState()->phrases.size() - 1)
    //{
        for (unsigned i = 0; i < dlMgr.getCurState()->answers.size(); ++i)
        {
            auto widg = m_dialWdg->getChild(std::string("answer ") + std::to_string(i));
            auto butt = dcast<Button*>(widg);
            butt->setGraphics(m_resSystem->textRenderer->renderSprSheet(dlMgr.getCurState()->answers[i].text, Font::latoRegular, FontSize::medium, m_opts->getInt("Width")));
            butt->setVisible(true);
        }
        for (unsigned i = dlMgr.getCurState()->answers.size(); i < dialMaxAnswers; ++i)
        {
            auto widg = m_dialWdg->getChild(std::string("answer ") + std::to_string(i));
            auto butt = dcast<Button*>(widg);
            butt->setVisible(false);
        }
    //}
}

bool GameGUI::updateCurSlot(std::vector<ItemSlot>& slots, ActSlotType slotsType, Vec2i coordStart)
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    for (size_t i = 0; i < slots.size(); ++i)
    {
        if (slots[i].isPointOn({ x, y }, coordStart))
        {
            m_currentSlot = &slots[i];
            m_currentSlotType = slotsType;
            m_currentSlotIndex = i;
            return true;
        }
    }
    return false;
}

void GameGUI::renderTextBuffer() const
{
    m_textBufferBack->render(*m_rendSubsystem, *m_resSystem);

	int size = m_journal->getSize();
    if (size > 0)
    {
        for (int i = size - 1; i >= 0 && i >= size - entriesToRender; --i)
        {
            auto title = m_resSystem->textRenderer->renderTexture(m_journal->getEntry(i), Font::latoRegular, FontSize::medium, Color::white);
            m_rendSubsystem->render(title, { 10, 120 - title->getHeight() * (size - 1 - i) });
        }
    }
}

void GameGUI::resetActiveSlot()
{
    m_activeSlot = nullptr;
    m_activeSlotType = ActSlotType::NONE;
    m_bagWdg->refresh();
}

void GameGUI::hidePanels()
{
    m_heroWdg->setVisible(false);

    resetActiveSlot();
    m_bagWdg->resetSlots();
    m_lootWdg->resetSlots();
    m_bagWdg->setVisible(false);
    m_lootWdg->setVisible(false);
}

void GameGUI::render() const
{
    int x, y;
    SDL_GetMouseState(&x, &y);

    renderTileFrame();
    renderTextBuffer();
    renderTextBuffer();
    for (auto& widget : m_widgets)
    {
        widget->render(*m_rendSubsystem, *m_resSystem);
    }
    if (m_activeSlot)
    {
        m_activeSlot->render(*m_rendSubsystem, *m_resSystem, { x, y });
    }
    m_slotHelper->render(*m_rendSubsystem, *m_resSystem);
    renderCursor();
}

void GameGUI::renderTileFrame() const
{
    int x, y;
    SDL_GetMouseState(&x, &y);

    auto& camera = m_sysManager->m_viewSystem->getCamera();

    auto viewport = camera.getViewport();
    if (!isPointOnGUI({ x, y }))
    {
        int newX = std::round((x - viewport.x - viewport.w / 2 - Camera::tileWidth / 2) / 1.0 / Camera::tileWidth);
        int newY = std::round((y - viewport.y - viewport.h / 2 - Camera::tileHeight / 2) / 1.0 / Camera::tileHeight);
        SDL_Rect dst = { viewport.x + viewport.w / 2 + newX * Camera::tileWidth,
                         viewport.y + viewport.h / 2 + newY * Camera::tileHeight,
                         Camera::tileWidth,
                         Camera::tileHeight };
        m_rendSubsystem->render(m_resSystem->get<Renderable>("tile_frame"), dst);
    }
}

void GameGUI::renderCursor() const
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    SDL_Rect dst = { x, y, 24, 24 };
    m_rendSubsystem->render(m_resSystem->get<Renderable>("cursor_simple"), dst);
}

} /* gui namespace. */