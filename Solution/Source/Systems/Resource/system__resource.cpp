#include "system__resource.h"

#include "factories.h"
#include "action_manager.h"
#include "system__dialogue.h"
#include "text_renderer.h"
#include "factions.h"

#include "subsystem__event.h"
#include "listener__dialogue.h"

#include "subsystem__rng.h"

// FIXME: load in opts
constexpr auto areadbPath = "Assets\\Databases\\areaDB.xml";
constexpr auto itemdbPath = "Assets\\Databases\\itemDB.json";
constexpr auto lootdbPath = "Assets\\Databases\\lootDB.json";
constexpr auto dialdbPath = "Assets\\Databases\\dialogueDB.json";
constexpr auto factionsDB = "Assets\\Databases\\factionsDB.xml";
constexpr auto widgdbPath = "Assets\\Databases\\widgetDB.json";
constexpr auto renddbPath = "Assets\\Databases\\rendDB.xml";
constexpr auto tsetdbPath = "Assets\\Databases\\tilesetDB.json";
constexpr auto actordbPath = "Assets\\Databases\\actorDB.json";

ResourceSystem::ResourceSystem() = default;

bool ResourceSystem::init(RenderSubsystem& rendSubsystem, RNGHolder& rngHolder, Options& opts)
{
    if (TTF_Init() == -1)
    {
        return false;
    }

    m_rngHolder = &rngHolder;

    factionsManager = new FactionsMgr();
    actionManager = new ActMgr();

    m_areaFactory.reset(new SceneFactory());
    m_dialogueFactory.reset(new DialFactory());
    m_itemFactory.reset(new ItemFactory());
    m_actionFactory.reset(new ActFactory(*this));
    m_widgetFactory.reset(new WidgetFactory());
    m_rendFactory.reset(new RenderableFactory());
    textRenderer = new TextRenderer();
	m_tilesetFactory.reset(new TilesetFactory());

    m_actorFactory.reset(new ActorFactory());
    m_componentFactory.reset(new ComponentFactory());

    m_widgetFactory->init(*this, opts);
    m_rendFactory->init(*this, rendSubsystem);
    textRenderer->init(*this, rendSubsystem);

    regFactory<gui::Widget>(m_widgetFactory.get());
    regFactory<Renderable>(m_rendFactory.get());

    auto initFlag = true;
    initFlag = initFlag && m_widgetFactory->load(widgdbPath);
    initFlag = initFlag && m_rendFactory->load(renddbPath);
    return initFlag;
}

bool ResourceSystem::initGame()
{
    m_areaFactory->init(*this);
	m_tilesetFactory->init(*this);
    m_actorFactory->init(*this);
    m_componentFactory->init(*this);

    regFactory<Scene>(m_areaFactory.get());
    regFactory<Item>(m_itemFactory.get());
    regFactory<Actor>(m_actorFactory.get());
    regFactory<ActorComponent>(m_componentFactory.get());
    regFactory<Tileset>(m_tilesetFactory.get());

    actionManager->init();
    dialogueManager = new DialManager(*m_dialogueFactory);

    auto listener = new DlListener(*dialogueManager);
    EventSubsystem::AddHandler(*listener);

    auto initFlag = true;
    initFlag = initFlag && m_actorFactory->load(actordbPath);
    initFlag = initFlag && m_componentFactory->load(actordbPath);
	initFlag = initFlag && m_tilesetFactory->load(tsetdbPath);
    initFlag = initFlag && m_itemFactory->load(itemdbPath);
    initFlag = initFlag && m_dialogueFactory->load(dialdbPath);
    factionsManager->load(factionsDB);

    return initFlag;
}

RNGHolder* ResourceSystem::getRNGHolder() const
{
    return m_rngHolder;
}

ResourceSystem::~ResourceSystem() = default;
