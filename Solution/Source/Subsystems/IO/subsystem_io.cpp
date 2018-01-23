#include "subsystem_io.h"

#include <filesystem>

InStream IOSubsystem::getInStream(const std::string& path)
{
    return std::ifstream(path);
}

OutStream IOSubsystem::getOutStream(const std::string& path)
{
    return std::ofstream(path);
}

std::unique_ptr<InStream> IOSubsystem::getInStream(const fs::path& path)
{
    return std::make_unique<std::ifstream>(path);
}

std::unique_ptr<OutStream> IOSubsystem::getOutStream(const fs::path& path)
{
    return std::make_unique<std::ofstream>(path);
}

std::unique_ptr<Json> IOSubsystem::getJSON(const std::string& path)
{
    auto result = std::make_unique<Json>();
    *result = nlohmann::json::parse(getInStream(path), nullptr, false);
    return result;
}
