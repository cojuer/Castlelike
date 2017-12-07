#pragma once

#include <any>
#include <map>
#include <string>

struct ActArgType
{
    static const std::string user;
    static const std::string scene;
    static const std::string coord;
    static const std::string duration;
    static const std::string power;
    static const std::string item;
};

using ActionArgs = std::map<std::string, std::any>;

template<typename T>
decltype(auto) get(ActionArgs& args, const std::string& key)
{
    return std::any_cast<T>(args.at(key));
}

template<typename T>
decltype(auto) get(const ActionArgs& args, const std::string& key)
{
    return std::any_cast<T>(args.at(key));
}