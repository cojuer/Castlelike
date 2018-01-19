#pragma once

#include <map>

#include "actor__storage.h"
#include "tile.h"
#include "vec2.h"

using SceneID = std::string;

class Item;

class Scene
{
    using Tiles      = std::vector<std::vector<Tile*>>;
    using ActorMap   = std::multimap<Coord, Actor*>;
    using ActorVec   = std::vector<Actor*>;

public:
    Scene();
    Scene(SceneID id, size_t width, size_t height, Tiles& tiles, ActorVec actors);

    void             addActor(Actor& actor);
    void             delActor(Actor& actor);
    void             relocateActor(Actor& actor, Coord coord);
    // FIXME: rework
    bool             addItem(Coord coord, Item* item);

    SceneID          getID() const;
    size_t           getWidth() const;
    size_t           getHeight() const;
    Tile*            getTile(Coord coord) const;
    // FIXME: delete this
    Actor*           getActor(Coord coord, const std::string& type) const;
    ActorVec         getActorsAtCoord(Coord coord) const;
    const std::map<ActorID, Actor*>& getIDToActorMap() const;

    bool             isEmpty(Coord) const;

    bool             fromJSON(const Json& node, ResourceSystem& resSystem);
    Json             toJSON() const;

    ~Scene();

private:
    SceneID          m_id;
    size_t           m_width;
    size_t           m_height;

    Tiles*           m_tiles;
    std::multimap<Coord, Actor*>   m_actorsByCoord;
    std::map<ActorID, Actor*> m_actorsById;
};