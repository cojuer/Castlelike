#pragma once

#include <list>
#include <memory>
#include <vector>

#include "object.h"
#include "vec2.h"

class ViewSystem;
class ActionInterface;
class Actor;
class Container;
class Equipment;
class GUIListener;
class JournalSystem;
class HandlerRegistration;
class Options;
class RenderSubsystem;
class ResourceSystem;
class SceneSystem;
union SDL_Event;

namespace gui {

class ActPanel;
class ActSlot;
class BagWidget;
class EquipmentWidget;
class ItemSlot;
class SlotHelper;
class Widget;

enum class ActSlotType
{
    NONE,
    BAG,
    EQUIP,
    LOOT,
    SHOP
};

/**
 * GameGUIState mostly influences handling options. For example,
 * in ACTION_INPUT m_state mouse click sets some input to current
 * action in action sheduler, in CUTSCENE there are only options
 * to pause, go to menu or skip. On ACTION_ANIM we cannot use
 * actions, but can get some info from map, quest log, etc.
 */
enum class GameGUIState
{
    NONE,
    NORMAL,
    ACTION_INPUT,
    ACTION_ANIM,
    CUTSCENE,
    DIALOGUE
};

class GameGUI final : public Object
{
    friend class ::GUIListener;

    static constexpr int entriesToRender = 7;

public:
    GameGUI();

    GameGUI(const GameGUI&) = delete;
    GameGUI(GameGUI&&) = delete;
    GameGUI& operator=(const GameGUI&) = delete;
    GameGUI& operator=(GameGUI&&) = delete;

    ~GameGUI();

    bool             init(Options& opts,
                          RenderSubsystem& rendSubsystem, 
                          ViewSystem& viewSystem,
                          JournalSystem& journalSystem,
                          SceneSystem& sceneSystem, 
                          ResourceSystem& resSystem);

    auto setState(GameGUIState state) -> void;

    void             initHeroBars();
    void             initHeroPanel();
    void             initInventory();
    void             initBagWidget();
    void             initActionsWdg();
    void             initDlMenu();

    void             renderTextBuffer() const;

    void             refreshDlMenu();

    bool             updateCurSlot(std::vector<ItemSlot>& slots, ActSlotType slotsType, Vec2i coordStart);

    void             render() const;
    void             renderTileFrame() const;
    void             renderCursor() const;

    void             resetActiveSlot();

    void             hidePanels();

    bool             isPointOnGUI(Vec2i point) const;

    void             handle(SDL_Event& event);

    bool             canHeroPerformAction();

private:
    void             handleDialogue(SDL_Event& event);
    void             handleInventory(SDL_Event& event);
    void             handleKeyboard(SDL_Event& event);

    void             handleStateNormal(SDL_Event& event);
    void             handleStateActInput(SDL_Event& event);
    void             handleStateActAnim(SDL_Event& event);
    void             handleStateCutscene(SDL_Event& event);
    void             handleStateDialogue(SDL_Event& event);

    void             updateCurSlot();

    bool             tryMoveBagToBag(Container& bag, SDL_Event& event) const;
    bool             tryMoveBagToLoot(Container& bag, Container& loot, SDL_Event& event) const;
    bool             tryMoveBagToEquip(Container& bag, Equipment& equip, SDL_Event& event) const;
    bool             tryMoveLootToBag(Container& loot, Container& bag, SDL_Event& event) const;
    bool             tryMoveLootToLoot(Container& loot, SDL_Event& event) const;
    bool             tryMoveLootToEquip(Container& loot, Container& bag, Equipment& equip, SDL_Event& event) const;
    bool             tryMoveEquipToBag(Container& bag, SDL_Event& event) const;
    bool             tryMoveEquipToLoot(Container& loot, SDL_Event& event) const;
    bool             tryMoveEquipToEquip(Container& bag, SDL_Event& event) const;

    bool             tryFastMoveLootToBag(Container& loot, Container& bag, SDL_Event& event) const;
    bool             tryFastMoveBagToEquip(Container& bag, Equipment& equip, SDL_Event& event) const;
    bool             tryFastMoveEquipToBag(Equipment& equip, Container& bag, SDL_Event& event) const;

private:
    // imported
    JournalSystem*     m_journalSystem{ nullptr };
    ResourceSystem*    m_resSystem{ nullptr };
    ViewSystem*        m_viewSystem{ nullptr };
    SceneSystem*       m_sceneSystem{ nullptr };
    RenderSubsystem*   m_rendSubsystem{ nullptr };

    Options*         m_opts{};
    Actor*           m_hero{};

    // owned
    GameGUIState     m_state;

    std::unique_ptr<Widget> m_hpWdg;
    std::unique_ptr<Widget> m_spWdg;
    std::unique_ptr<Widget> m_xpWdg;
    std::unique_ptr<Widget> m_inventoryWdg;
    std::unique_ptr<Widget> m_textBufferBack;
    std::unique_ptr<Widget> m_heroWdg;
    std::unique_ptr<ActPanel>  m_actionsWdg;
    std::unique_ptr<BagWidget> m_lootWdg;
    std::unique_ptr<Widget> m_dialWdg;

    BagWidget*       m_bagWdg{};
    EquipmentWidget* m_equipWdg{};

    std::unique_ptr<SlotHelper> m_slotHelper;

    // used
    std::list<Widget*> m_widgets;

    ItemSlot*        m_activeSlot{};
    ActSlotType      m_activeSlotType;
    int              m_activeSlotIndex{};

    ItemSlot*        m_currentSlot{};
    ActSlotType      m_currentSlotType;
    int              m_currentSlotIndex{};

    std::unique_ptr<ActionInterface> m_action{};

    std::unique_ptr<HandlerRegistration> m_reg;
    std::unique_ptr<GUIListener> m_listener;
};

} /* gui namespace. */