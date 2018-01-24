#include "factory__scene.h"

#include "system__resource.h"

#include "tile.h"
#include "tileset.h"

bool SceneFactory::init(ResourceSystem& resSystem)
{
    m_resSystem = &resSystem;
    return true;
}

bool SceneFactory::isPlaceForRoom(Coord leftTop,
                                 int width,
                                 int height,
                                 int areaw,
                                 int areah,
                                 std::string** tiles)
{
    if (leftTop.x < 0 ||
        leftTop.x + width >= areaw ||
        leftTop.y < 0 ||
        leftTop.y + height >= areah)
    {
        return false;
    }
    for (int y = leftTop.y; y < leftTop.y + height - 1; ++y)
    {
        for (int x = leftTop.x; x < leftTop.x + width - 1; ++x)
        {
            if (tiles[y][x] != "none")
            {
                return false;
            }
        }
    }
    return true;
}

bool SceneFactory::createRoom(Coord entrance,
                             Direction dir,
                             RNG& rng,
                             int areaw,
                             int areah,
                             std::string** tiles,
                             std::vector<RoomModel>& rooms,
                             bool hasEntrance)
{
    int width = rng.getFrom(5, 8);
    int height = rng.getFrom(5, 8);
    Coord leftTop;
    int shift = rng.getFrom(1, width < height ? width - 2 : height - 2);
    switch (dir)
    {
    case Direction::UPWARD:
        leftTop = { entrance.x - shift, entrance.y - height };
        break;
    case Direction::LEFTWARD:
        leftTop = { entrance.x - width, entrance.y - shift };
        break;
    case Direction::DOWNWARD:
        leftTop = { entrance.x - shift, entrance.y + 1 };
        break;
    case Direction::RIGHTWARD:
        leftTop = { entrance.x + 1, entrance.y - shift };
        break;
    }

    if (isPlaceForRoom(leftTop, width, height, areaw, areah, tiles))
    {
        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                if (i == 0 || j == 0 || i == height - 1 || j == width - 1)
                {
                    tiles[leftTop.y + i][leftTop.x + j] = "wall";
                }
                else
                {
                    tiles[leftTop.y + i][leftTop.x + j] = "ground";
                }
            }
        }

        if (leftTop.y > 0)
        {
            for (int j = 0; j < width; ++j)
            {
                if (tiles[leftTop.y][leftTop.x + j] == "wall")
                {
                    tiles[leftTop.y - 1][leftTop.x + j] = "wall";
                }
            }
        }

        if (hasEntrance)
        {
            tiles[entrance.y][entrance.x] = "ground";

            switch (dir)
            {
            case Direction::UPWARD:
                tiles[entrance.y - 1][entrance.x] = "ground";
                break;
            case Direction::LEFTWARD:
                tiles[entrance.y][entrance.x - 1] = "ground";
                break;
            case Direction::DOWNWARD:
                tiles[entrance.y + 1][entrance.x] = "ground";
                break;
            case Direction::RIGHTWARD:
                tiles[entrance.y][entrance.x + 1] = "ground";
                break;
            }
        }
        rooms.push_back(RoomModel(leftTop, width, height));
        return true;
    }
    return false;
}

SceneFactory::~SceneFactory() {}

/* FIXME: reconsider areafactory usage */
bool SceneFactory::load(const std::string& fname)
{
    return true;
}

Resource<Scene>* SceneFactory::get(ResourceId& id)
{
    auto tset = m_resSystem->get<Tileset>("test_tileset");
    auto& floor = *tset->getTile(tset->m_terrains.at("floor").m_tiles.front());
    auto& wall = *tset->getTile(tset->m_terrains.at("wall").m_tiles.front());
    auto& walltop = *tset->getTile(tset->m_terrains.at("walltop").m_tiles.front());

    uint32_t width = 100;
    uint32_t height = 100;
    auto& area = *new std::vector<std::vector<Tile*>>(height, std::vector<Tile*>(width));

    RNG rng{ 0 };

    std::vector<RoomModel> rooms;

	std::string** tileTypes = new std::string*[height];
    for (int i = 0; i < height; ++i)
    {
        tileTypes[i] = new std::string[width];
    }
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            tileTypes[i][j] = "none";
        }
    }

    while (rooms.size() < 1)
    {
        Coord center(rng.getFrom(7, width - 7), rng.getFrom(7, height - 7));
        createRoom(center, Direction::DOWNWARD, rng, width, height, tileTypes, rooms, false);
    }

    int counter = 0;
    while (rooms.size() < 100 && counter < 1000)
    {
        int dir = rng.getFrom(0, 3);
        int roomToExpand = rng.getFrom(0, rooms.size() - 1);
        Coord entrance = rooms[roomToExpand].getRandomWallTile(static_cast<Direction>(dir + 1));
        if (createRoom(entrance, static_cast<Direction>(dir + 1), rng, width, height, tileTypes, rooms, true))
        {
            counter = 0;
        }
        else
        {
            ++counter;
        }
    }

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if (tileTypes[i][j] == "ground")
            {
                area[i][j] = &floor;
            }
            else if (tileTypes[i][j] == "wall")
            {
                area[i][j] = &wall;
            }
        }
    }
    for (int i = 0; i < height - 1; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if (area[i + 1][j] != nullptr &&
                area[i][j] != nullptr &&
				tileTypes[i + 1][j] == "wall" &&
				tileTypes[i][j] == "wall")
            {
                area[i][j] = &walltop;
            }
            if (area[i + 1][j] == nullptr &&
                area[i][j] != nullptr &&
				tileTypes[i][j] == "wall")
            {
                area[i][j] = &walltop;
            }
        }
    }

	for (int i = 0; i < height; ++i)
	{
		delete[](tileTypes[i]);
	}
	delete[](tileTypes);

    auto scene = new Scene{ "test", width, height, area, std::vector<Actor*>{} };

    return scene;
}