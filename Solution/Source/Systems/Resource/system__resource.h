#pragma once

#include <any>
#include <map>
#include <memory>
#include <typeindex>

#include "factory.h"
#include "options.h"

#include "resource.h"
#include "journal.h"

// FIXME: these includes can be deleted 
// if Renderable and Widget are defined
// where get<...> is used.
#include "widget.h"

class RenderSubsystem;
class TextRenderer;
class ActMgr;
class DialManager;
class FactionsMgr;
class RNG;
class RNGHolder;

class ActFactory;
class ActorFactory;
class ComponentFactory;
class DialFactory;
class ItemFactory;
class RenderableFactory;
class SceneFactory;
class TilesetFactory;
class WidgetFactory;

class ResourceSystem
{
public:
    ResourceSystem();

    bool init(RenderSubsystem& rendSubsystem, RNGHolder& rngHolder, Options& opts);
    bool initGame();

    RNGHolder* getRNGHolder() const;

    template<typename T>
    Resource<T>* get(const std::string& res);

    template<typename T>
    void regFactory(Factory<T>* loader);

    ~ResourceSystem();

public:
    ActMgr*          actionManager;
    DialManager*     dialogueManager;
    FactionsMgr*     factionsManager;
    TextRenderer*    textRenderer;

    // TODO: move somewhere else
    Journal*         m_journal;

    std::unique_ptr<ActFactory>        m_actionFactory;
    std::unique_ptr<ItemFactory>       m_itemFactory;
    std::unique_ptr<SceneFactory>      m_areaFactory;
    std::unique_ptr<DialFactory>       m_dialogueFactory;
    std::unique_ptr<WidgetFactory>     m_widgetFactory;
    std::unique_ptr<RenderableFactory> m_rendFactory;
    std::unique_ptr<TilesetFactory>    m_tilesetFactory;
    std::unique_ptr<ActorFactory>      m_actorFactory;
    std::unique_ptr<ComponentFactory>  m_componentFactory;

private:
    std::map<std::type_index, std::any> factories;
    RNGHolder* m_rngHolder;
};

template<typename T>
Resource<T>* ResourceSystem::get(const std::string& res)
{
    auto iter = factories.find(typeid(T));
    if (iter != factories.end())
    {
        return std::any_cast<Factory<T>*>(iter->second)->get(res);
    }
    return nullptr;
}

template<typename T>
void ResourceSystem::regFactory(Factory<T>* loader)
{
    factories[typeid(T)] = loader;
}