#include "scene.h"

#include <iostream>

#include "container.h"
#include "utils.h"
#include "system__actor_id.h"
#include "tileset.h"

#include "system__resource.h"
#include "factory__actor.h"

Scene::Scene() :
    m_tiles(nullptr)
{}

Scene::Scene(SceneID id, size_t width, size_t height, Tiles& tiles, ActorVec actors) :
    m_id(id),
    m_width(width),
    m_height(height),
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
    assert(node.find("tileset") != node.end());
    assert(!node.at("tileset").is_null() && "tilesets cannot be loaded");
    auto tset = resSystem.get<Tileset>(node.at("tileset").get<std::string>());

    // FIXME: load
    m_width = 100;
    m_height = 100;
    m_tiles = new std::vector<std::vector<Tile*>>(m_height, std::vector<Tile*>(m_width));

    assert(!node.at("tiles").is_null() && "tiles cannot be loaded");
    auto tilesNode = node.at("tiles");
    auto x = 0;
    auto y = 0;
    for (auto it = tilesNode.begin(); it != tilesNode.end(); ++it)
    {
        if (it->get<int>() != -1)
            (*m_tiles)[y][x] = tset->getTile(it->get<int>());
        ++x;
        if (x == m_width)
        {
            x = 0;
            ++y;
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

    // get tileset (should be reworked)
    for (const auto& row : *m_tiles)
    {
        for (const auto& elem : row)
        {
            if (elem) result["tileset"] = elem->getTileset()->m_resID;
        }
    }

    Json tilesNode;
    for (const auto& row : *m_tiles)
    {
        for (const auto& elem : row)
        {
            if (elem) tilesNode.push_back(elem->getID());
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
    if (coord.x < 0 || coord.x >= m_width || 
        coord.y < 0 || coord.y >= m_height)
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
        auto cont = new Container(36);
        areaCont = new StorageActor(IDManager::instance().getActorID(), coord, "items_pile", false, *cont, false);
        m_actorsByCoord.insert(std::pair<Coord, Actor*>(coord, areaCont));
        cont->add(*item);
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

