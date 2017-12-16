#include "factory__area.h"

#include "resource_manager.h"

bool SceneFactory::init(ResourceManager& resManager)
{
    m_resManager = &resManager;
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
    auto width = rng.getInRange(5, 8);
    auto height = rng.getInRange(5, 8);
    Coord leftTop;
    int shift = rng.getInRange(1, width < height ? width - 2 : height - 2);
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

Resource<std::vector<std::vector<Tile*>>>* SceneFactory::get(ResourceId& id)
{
    RNG rng;

    auto width = 20;
    auto height = 20;

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
        Coord center(rng.getInRange(7, width - 7), rng.getInRange(7, height - 7));
        createRoom(center, Direction::DOWNWARD, rng, width, height, tileTypes, rooms, false);
    }

    int counter = 0;
    while (rooms.size() < 10 && counter < 1000)
    {
        int dir = rng.getInRange(0, 3);
        int roomToExpand = rng.getInRange(0, rooms.size() - 1);
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

    auto& tiles = (*new std::vector<std::vector<Tile*>>(height, std::vector<Tile*>(width)));
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if (tileTypes[i][j] == "ground")
            {
                
                tiles[i][j] = new Tile(m_resManager->get<Renderable>("tile_proto_ground_0"), false);
            }
            else if (tileTypes[i][j] == "wall")
            {
                tiles[i][j] = new Tile(m_resManager->get<Renderable>("tile_proto_wall_0"), true);
            }
            else 
            {
                tiles[i][j] = nullptr;
            }
        }
    }
    for (int i = 0; i < height - 1; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if (tiles[i + 1][j] != nullptr && 
                tiles[i][j] != nullptr && 
				tileTypes[i + 1][j] == "wall" &&
				tileTypes[i][j] == "wall")
            {
                tiles[i][j] = new Tile(m_resManager->get<Renderable>("tile_proto_walltop_0"), true);
            }
            if (tiles[i + 1][j] == nullptr && 
                tiles[i][j] != nullptr && 
				tileTypes[i][j] == "wall")
            {
                tiles[i][j] = new Tile(m_resManager->get<Renderable>("tile_proto_walltop_0"), true);
            }
        }
    }

	for (int i = 0; i < height; ++i)
	{
		delete[](tileTypes[i]);
	}
	delete[](tileTypes);

    return &tiles;
}