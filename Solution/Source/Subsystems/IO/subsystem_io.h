#pragma once

#include <fstream>
#include <memory>

#include "json.hpp"

// TODO: rework when fs will not be experimental
namespace fs = std::experimental::filesystem;

using Json = nlohmann::json;

using InStream = std::ifstream;
using OutStream = std::ofstream;

class IOSubsystem
{
public:
    static InStream  getInStream(const std::string& path);
    static OutStream getOutStream(const std::string& path);

    static std::unique_ptr<InStream>  getInStream(const fs::path& path);
    static std::unique_ptr<OutStream> getOutStream(const fs::path& path);

    static std::unique_ptr<Json> getJSON(const std::string& path);
};
