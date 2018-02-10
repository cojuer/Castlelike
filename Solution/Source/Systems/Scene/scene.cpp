#include "scene.h"

#include "container.h"
#include "utils.h"
#include "system__actor_id.h"
#include "tileset.h"

#include "system__resource.h"
#include "factory__actor.h"

Scene::Scene() :
    m_width(0),
    m_height(0),
    m_tiles(nullptr)
{}

Scene::Scene(SceneID id, 
             size_t width, 
             size_t height, 
             Tilesets tilesets,
             Tiles& tiles, 
             ActorVec actors) :
    m_id(std::move(id)),
    m_width(width),
    m_height(height),
    m_tilesets(std::move(tilesets)),
    m_tiles(&tiles)
{
    for (auto actor : actors)
    {
        addActor(*actor);
    }
}

void Scene::addActor(Actor& actor)
{
    m_actorsById[actor.getID()] = &actor;
    m_actorsByCoord.insert({ actor.getCoord(), &actor });
}

void Scene::delActor(Actor& actor)
{
    auto range = m_actorsByCoord.equal_range(actor.getCoord());
    for (auto iter = range.first; iter != range.second; ++iter)
    {
        if (iter->second->getID() == actor.getID())
        {
            m_actorsByCoord.erase(iter);
            break;
        }
    }
    m_actorsById.erase(actor.getID());
}

void Scene::relocateActor(Actor& actor, Coord coord)
{
    delActor(actor);
    actor.setCoord(coord);
    addActor(actor);
}

size_t Scene::getWidth() const
{
    return m_width;
}

size_t Scene::getHeight() const
{
    return m_height;
}

bool Scene::isEmpty(Coord coord) const
{
    auto empty = true;
    auto range = m_actorsByCoord.equal_range(coord);
    for (auto iter = range.first; iter != range.second; ++iter)
    {
        empty = empty && !(iter->second->isCollisive());
    }
    empty = empty && !(*m_tiles)[coord.y][coord.x]->isCollisive();
    return empty;
}

bool Scene::fromJSON(const Json& node, ResourceSystem& resSystem)
{
    m_width = node.at("width");
    m_height = node.at("height");

    assert(node.find("tilesets") != node.end());
    assert(!node.at("tilesets").is_null() && "tilesets cannot be loaded");
    auto tsetsNode = node.at("tilesets");
    for (auto it = tsetsNode.begin(); it != tsetsNode.end(); ++it)
    {
        auto tsetResID = it->get<std::string>();
        auto tset = resSystem.get<Tileset>(tsetResID);
        m_tilesets.push_back(tset);
    }

    // TEST: vs solution with map
    std::vector<std::pair<int32_t, Tileset*>> tileIdToInfo;
    auto offset = 0;
    for (auto tileset : m_tilesets)
    {
        tileIdToInfo.insert(tileIdToInfo.end(), tileset->getSize(), { offset, tileset });
        offset += tileset->getSize();
    }


    m_tiles = new std::vector<std::vector<Tile*>>(m_height, std::vector<Tile*>(m_width));

    assert(!node.at("tiles").is_null() && "tiles cannot be loaded");
    auto tilesNode = node.at("tiles");
    auto tileIter = tilesNode.begin();
    for (uint32_t y = 0; y < m_height; ++y)
    {
        for (uint32_t x = 0; x < m_width; ++x)
        {
            auto tileID = tileIter->get<int>();
            if (tileID != -1)
            {
                auto[offset, tset] = tileIdToInfo.at(tileID);
                (*m_tiles)[y][x] = tset->getTile(tileID - offset);
            }
            ++tileIter;
        }
    }

    assert(!node.at("actors").is_null() && "actors cannot be loaded");
    auto actorsNode = node.at("actors");
    for (auto it = actorsNode.begin(); it != actorsNode.end(); ++it)
    {
        auto actor = resSystem.m_actorFactory->loadActor(*it);
        m_actorsById[actor->getID()] = actor;
        m_actorsByCoord.insert({ actor->getCoord(), actor });
    }

    return true;
}

Json Scene::toJSON() const
{
    Json result;

    result["width"] = m_width;
    result["height"] = m_height;

    std::vector<std::string> tilesets;
    for (auto tileset : m_tilesets)
    {
        tilesets.push_back(tileset->getResID());
    }
    result["tilesets"] = tilesets;

    std::map<std::string, uint32_t> offsets;
    auto offset = 0;
    for (auto tileset : m_tilesets)
    {
        offsets[tileset->getResID()] = offset;
        offset += tileset->getSize();
    }

    Json tilesNode;
    for (const auto& row : *m_tiles)
    {
        for (const auto& elem : row)
        {
            if (elem)
            {
                offset = offsets.at(elem->getTileset());
                tilesNode.push_back(offset + elem->getID());
            }
            else tilesNode.push_back(-1);
        }
    }
    result["tiles"] = tilesNode;

    Json actorsNode;
    for (auto&[id, actor] : m_actorsById)
    {
        actorsNode.push_back(actor->toJSON());
    }
    result["actors"] = actorsNode;
    
    return result;
}

Scene::ActorVec Scene::getActorsAtCoord(Coord coord) const
{
    std::vector<Actor*> result;
    auto range = m_actorsByCoord.equal_range(coord);
    for (auto iter = range.first; iter != range.second; ++iter)
    {
        result.push_back(iter->second);
    }
    return result;
}

Actor* Scene::getHero() const
{
    auto iter = m_actorsById.find(IDManager::heroID);
    return iter != m_actorsById.end() ? iter->second : nullptr;
}

const std::map<ActorID, Actor*>& Scene::getIDToActorMap() const
{
    return m_actorsById;
}

// FIXME: Delete out of scene check 
Tile* Scene::getTile(Coord coord) const
{
    if (coord.x < 0 || int64_t(coord.x) >= int64_t(m_width) || 
        coord.y < 0 || int64_t(coord.y) >= int64_t(m_height))
    {
        return nullptr;
    }

    return (*m_tiles)[coord.y][coord.x];
}

Actor* Scene::getActor(Coord coord, const std::string& type) const
{
    auto range = m_actorsByCoord.equal_range(coord);
    for (auto iter = range.first; iter != range.second; ++iter)
    {
        if (iter->second->getType() == type)
        {
            return dcast<Actor*>(iter->second);
        }
    }
    return nullptr;
}

Actor* Scene::getActor(ActorID id) const
{
    auto iter = m_actorsById.find(id);
    return iter != m_actorsById.end() ? iter->second : nullptr;
}

// TODO: pass item by reference
bool Scene::addItem(Coord coord, Item* item)
{
    auto areaCont = dcast<StorageActor*>(getActor(coord, ActorType::CONTAINER));
    if (areaCont)
    {
        if (areaCont->getContainer().isFull()) return false;
        areaCont->getContainer().add(*item);
        return true;
    }
    else
    {
        Container cont{ 36 };
        cont.add(*item);
        areaCont = new StorageActor(IDManager::instance().getActorID(), coord, "items_pile", false, std::move(cont), false);
        m_actorsByCoord.insert(std::pair<Coord, Actor*>(coord, areaCont));
        return true;
    }
}

SceneID Scene::getID() const
{
    return m_id;
}

Scene::~Scene()
{
    delete(m_tiles);

    for (auto& [id, actor] : m_actorsById)
    {
        delete(actor);
    }
}

