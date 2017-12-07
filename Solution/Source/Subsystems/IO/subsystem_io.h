#pragma once

#include <fstream>
#include <memory>

#include "json.hpp"

using Json = nlohmann::json;

using InStream = std::ifstream;
using OutStream = std::ofstream;

class IOSubsystem
{
public:
    static InStream  getInStream(const std::string& path);
    static OutStream getOutStream(const std::string& path);

    static std::unique_ptr<Json> getJSON(const std::string& path);
};
