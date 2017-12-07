#include "scene.h"

#include "container.h"
#include "utils.h"
#include "id_manager.h"

Scene::Scene(SceneID id, Tiles& tiles, ActorVec actors) :
    m_id(id),
    m_width(tiles.front().size()),
    m_height(tiles.size()),
    m_tiles(tiles)
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
    empty = empty && !m_tiles[coord.y][coord.x]->isCollisive();
    return empty;
}

Json Scene::toJSON() const
{
    Json result;
    // FIXME: use auto&[] when proper support will be available
    for (auto& pair : m_actorsById)
    {
        result[pair.first] = pair.second->toJSON();
    }
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
    return m_tiles[coord.y][coord.x];
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

// TODO: pass item by reference
bool Scene::addItem(Coord coord, Item* item)
{
    auto areaCont = dcast<StorageActor*>(getActor(coord, "cont"));
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
    delete(&m_tiles);
}

