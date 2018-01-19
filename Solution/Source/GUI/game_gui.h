#pragma once

#include <list>
#include <vector>

#include "object.h"
#include "vec2.h"
#include "container.h"
#include "equipment.h"
#include "action_interface.h"

class RenderSubsystem;
class Actor;
class Journal;
class GUIListener;
class Options;
class ResourceSystem;
class SceneSystem;
class GameSystemManager;
union SDL_Event;

namespace gui {

class ActSlot;
class BagWidget;
class EquipmentWidget;
class ItemSlot;
class Widget;
class ProgressBar;
class ActPanel;
class SlotHelper;
class ViewData;

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
    CUTSCENE
};

class GameGUI final : public Object
{
    friend class GUIListener;

    static constexpr int entriesToRender = 7;

public:
    GameGUI();

    ~GameGUI();

    bool             init(Options& opts,
                          RenderSubsystem&  rendSubsystem, 
                          GameSystemManager&    sysManager, 
                          SceneSystem&     sceneSystem, 
                          ResourceSystem&  resSystem);

    void             initHeroBars();
    void             initHeroPanel();
    void             initInventory();
    void             initBagWidget();
    void             initActionsWdg();
    void             initJournalPanel();
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

private:
    void             handleInventory(SDL_Event& event);
    void             handleKeyboard(SDL_Event& event);

    void             handleNormal(SDL_Event& event);
    void             handleActInput(SDL_Event& event);
    void             handleActAnim(SDL_Event& event);
    void             handleCutscene(SDL_Event& event);

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
    ResourceSystem* m_resSystem;
    GameSystemManager*   m_sysManager;
    SceneSystem*    m_sceneSystem;
    RenderSubsystem* m_rendSubsystem;

    Options*         m_opts;
    Actor*           m_hero;
    Journal*         m_journal;

    // owned
    GameGUIState     m_state;

    std::unique_ptr<Widget> m_hpWdg;
    std::unique_ptr<Widget> m_spWdg;
    std::unique_ptr<Widget> m_xpWdg;
    std::unique_ptr<Widget> m_inventoryWdg;
    std::unique_ptr<Widget> m_textBufferBack;
    std::unique_ptr<Widget> m_heroWdg;
    std::unique_ptr<ActPanel>  m_actionsWdg;
    std::unique_ptr<BagWidget> m_bagWdg;
    std::unique_ptr<BagWidget> m_lootWdg;
    std::unique_ptr<EquipmentWidget> m_equipWdg;
    std::unique_ptr<Widget> m_journalWdg;
    std::unique_ptr<Widget> m_dialWdg;

    std::unique_ptr<SlotHelper> m_slotHelper;

    // used
    std::list<Widget*> m_widgets;

    ActSlot*         m_activeSkillSlot;

    ItemSlot*        m_activeSlot;
    ActSlotType      m_activeSlotType;
    int              m_activeSlotIndex;

    ItemSlot*        m_currentSlot;
    ActSlotType      m_currentSlotType;
    int              m_currentSlotIndex;

    ActionInterface* m_action;
};

} /* gui namespace. */