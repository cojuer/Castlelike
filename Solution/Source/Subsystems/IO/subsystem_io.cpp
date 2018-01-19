#include "subsystem_io.h"

InStream IOSubsystem::getInStream(const std::string& path)
{
    return std::ifstream(path);
}

OutStream IOSubsystem::getOutStream(const std::string& path)
{
    return std::ofstream(path);
}

std::unique_ptr<Json> IOSubsystem::getJSON(const std::string& path)
{
    auto result = std::make_unique<Json>();
    *result = nlohmann::json::parse(getInStream(path), nullptr, false);
    return result;
}
