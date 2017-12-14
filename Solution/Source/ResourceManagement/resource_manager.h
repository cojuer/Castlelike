#pragma once

#include <any>
#include <map>
#include <memory>
#include <typeindex>

#include "factory.h"
#include "options.h"

#include "resource.h"
#include "journal.h"

#include "renderable.h"
#include "widget.h"

class RenderSubsystem;
class NewSceneFactory;
class ActFactory;
class ItemFactory;
class SceneFactory;
class DialFactory;
class WidgetFactory;
class RenderableFactory;
class TextRenderer;
class TilesetFactory;
class ActMgr;
class DialManager;
class FactionsMgr;

class ActorFactory;
class ComponentFactory;

class ResourceManager
{
public:
    ResourceManager();

    bool init(RenderSubsystem& rendSubsystem, Options& opts);
    bool initGame();

    template<typename T>
    Resource<T>* get(const std::string& res);

    template<typename T>
    void regFactory(Factory<T>* loader);

    ~ResourceManager();

public:
    ActMgr*          actionManager;
    DialManager*     dialogueManager;
    FactionsMgr*     factionsManager;
    TextRenderer*    textRenderer;

    // TODO: move somewhere else
    Journal*         m_journal;

    std::unique_ptr<NewSceneFactory>   m_newSceneFactory;
    std::unique_ptr<ActFactory>        m_actionFactory;
    std::unique_ptr<ItemFactory>       m_itemFactory;
    std::unique_ptr<SceneFactory>      m_areaFactory;
    std::unique_ptr<DialFactory>       m_dialogueFactory;
    std::unique_ptr<WidgetFactory>     m_widgetFactory;
    std::unique_ptr<RenderableFactory> m_rendFactory;
    std::unique_ptr<TilesetFactory>    m_tilesetFactory;
    std::unique_ptr<ActorFactory>      m_actorFactory;
    std::unique_ptr<ComponentFactory>  m_componentFactory;

    std::map<std::type_index, std::any> factories;
};

template<typename T>
Resource<T>* ResourceManager::get(const std::string& res)
{
    auto iter = factories.find(typeid(T));
    if (iter != factories.end())
    {
        return std::any_cast<Factory<T>*>(iter->second)->get(res);
    }
    return nullptr;
}

template<typename T>
void ResourceManager::regFactory(Factory<T>* loader)
{
    factories[typeid(T)] = loader;
}