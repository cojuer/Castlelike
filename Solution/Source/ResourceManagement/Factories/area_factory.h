#pragma once

#include "factory.h"
#include "room.h"
#include "tile.h"
#include "rng.h"
#include "scene.h"

class ResourceManager;

class SceneFactory : public Factory<std::vector<std::vector<Tile*>>>
{
public:
    SceneFactory() = default;

    bool init(ResourceManager& resManager);

    bool load(const std::string& fname) override;
    Resource<std::vector<std::vector<Tile*>>>* get(ResourceId& id) override;

    static bool      isPlaceForRoom(Coord leftTop,
                                    int roomw,
                                    int roomh,
                                    int areaw,
                                    int areah,
                                    std::string** tiles);

    bool             createRoom(Coord entrance,
                                Direction dir,
                                RNG& rng,
                                int areaw,
                                int areah,
                                std::string** tiles,
                                std::vector<RoomModel>& rooms,
                                bool hasEntrance);

    ~SceneFactory() override;
private:
    ResourceManager* m_resManager;
};