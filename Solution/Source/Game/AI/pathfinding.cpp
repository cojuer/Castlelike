#include "pathfinding.h"

#include "scene.h"
#include "utils.h"

namespace ai {

AStarAlgorithm::Path AStarAlgorithm::findPath(Scene& scene, Coord fr, Coord to)
{
    PriorityQueue openNodes;
    std::map<Coord, Coord> cameFrom;
    std::map<Coord, int>   distGone;

    openNodes.put(fr, 0);
    cameFrom[fr] = fr;
    distGone[fr] = 0;

    while (!openNodes.empty()) 
    {
        auto current = openNodes.get();

        if (current == to) break;

        for (auto neighbour : neighbours(scene, current)) 
        {
            if (!scene.isEmpty(neighbour) && neighbour != to) continue;
            auto distance = distGone.at(current) + neighbourDist;
            if (distance > maxDist) continue;
            if (cameFrom.find(neighbour) == cameFrom.end() || 
                distance < distGone.at(neighbour)) 
            {
                double priority = distance + utils::euclDist(neighbour, to);
                openNodes.put(neighbour, priority);
                cameFrom[neighbour] = current;
                distGone[neighbour] = distance;
            }
        }
    }
    if (cameFrom.find(to) == cameFrom.end())
    {
        return Path();
    }
    else
    {
        auto result = Path();
        Coord current{ to };
        do
        {
            result.push_front(current);
            current = cameFrom.at(current);
        } while (cameFrom.at(current) != current);
        return result;
    }
};

std::vector<Coord> AStarAlgorithm::neighbours(Scene& scene, Coord coord)
{
    return std::vector<Coord>{
        { coord.x + 1, coord.y },
        { coord.x - 1, coord.y },
        { coord.x, coord.y + 1 },
        { coord.x, coord.y - 1 }
    };
}

} /* AI namespace */