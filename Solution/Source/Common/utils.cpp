#include "utils.h"

#include <cassert>
#include <cmath>
#include <iostream>
#include <string>

namespace utils
{

void logassert(bool expression, const std::string& info)
{
    if (!expression)
    {
        std::cout << "Assertion info: " << info << std::endl;
        assert(expression);
    }
}

int coordDist(Vec2i a, Vec2i b)
{
    return abs(a.x - b.x) + abs(a.y - b.y);
}

int euclDist(Vec2i a, Vec2i b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

std::string format(std::string& str, std::vector<std::string>& args)
{
    std::vector<std::pair<int, int>> words;
    std::vector<bool> isArg;
    std::pair<int, int> word = {0, 0};
    for (size_t i = 0; i < str.size(); ++i)
    {
        if (str[i] == '{' || str[i] == '}')
        {
            word.second = i - 1;
            if (word.second >= word.first)
            {
                words.push_back(word);
                if (str[i] == '}') isArg.push_back(true);
                else isArg.push_back(false);
            }
            word = { i + 1, 0 };
        }
    }
    word.second = str.size() - 1;
    if (word.second >= word.first)
    {
        words.push_back(word);
        isArg.push_back(false);
    }
    std::string result("");
    for (size_t i = 0; i < words.size(); ++i)
    {
        word = words[i];
        auto substr = str.substr(word.first, word.second - word.first + 1);
        if (isArg[i]) result += args[std::stoi(substr)];
        else result += substr;
    }
    std::cout << result << std::endl;
    return result;
}

}
