#pragma once

#include "factory.h"
#include "room.h"
#include "tile.h"
#include "rng.h"
#include "scene.h"

class ResourceSystem;

class SceneFactory : public Factory<Scene>
{
public:
    SceneFactory() = default;

    bool init(ResourceSystem& resSystem);

    bool load(const std::string& fname) override;
    Resource<Scene>* get(ResourceId& id) override;

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
    ResourceSystem* m_resSystem;
};