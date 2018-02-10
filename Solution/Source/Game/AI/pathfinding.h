#pragma once

#include <functional>
#include <queue>
#include <list>
#include <vector>

#include "vec2.h"

class Scene;

namespace ai {

class AStarAlgorithm
{
    struct PriorityQueue {
        using Elem = std::pair<int, Coord>;
        std::priority_queue<Elem, std::vector<Elem>, std::greater<>> elements;

        bool empty() const { return elements.empty(); }

        void put(Coord item, int priority) 
        {
            elements.push(std::make_pair(priority, item));
        }

        Coord get() 
        {
            auto result = elements.top().second;
            elements.pop();
            return result;
        }
    };

    static constexpr auto neighbourDist = 1;
    static constexpr auto maxDist = 15;

    using Path = std::list<Coord>;
public:
    static Path findPath(Scene& scene, Coord fr, Coord to);
private:
    static std::vector<Coord> neighbours(Scene& scene, Coord coord);
};

}