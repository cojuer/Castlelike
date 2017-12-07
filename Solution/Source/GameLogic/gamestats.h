#pragma once

#include <map>
#include <variant>

// FIXME: rework and start using
struct GameStats
{
    std::map<std::string, std::variant<bool, int, std::string>> stats;
};
