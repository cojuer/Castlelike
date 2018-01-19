#include "system__save.h"

#include <algorithm>
#include <iostream>
#include <filesystem>
#include <iterator>
#include "subsystem_io.h"

namespace fs = std::experimental::filesystem;

const std::string SaveSystem::extension = ".json";
const std::string SaveSystem::format = "CASTLELIKE_SAVEFILE";

bool SaveSystem::init()
{
    fs::path profPath("Profiles");

    fs::directory_iterator begin(profPath);
    fs::directory_iterator end;
    
    // Discover all profile folders
    std::vector<fs::path> profDirs;
    std::copy_if(begin, end, std::back_inserter(profDirs), 
        [](const fs::path& path)
        {
            return fs::is_directory(path);
        });

    for (const auto& profDir : profDirs)
    {
        std::cout << profDir << std::endl;
    }
    std::cout << profDirs.size() << std::endl;

    // Discover saves for each profile
    for (const auto& profDir : profDirs)
    {
        fs::directory_iterator profDirBegin(profDir);
        fs::directory_iterator profDirEnd;
        std::vector<fs::path> savePaths;
        std::copy_if(profDirBegin, profDirEnd, std::back_inserter(savePaths),
            [](const fs::path& path)
            {
                return fs::is_regular_file(path);
            });
        for (const auto& savePath : savePaths)
        {
            if (savePath.extension() != extension) continue;
            auto saveJson = IOSubsystem::getJSON(savePath.string());
            if (!saveJson->is_object() 
                or saveJson->find("format") == saveJson->end() 
                or saveJson->at("format") != format)
            {
                std::cout << "Invalid file: " << savePath << std::endl;
                continue;
            }
            // TODO: save
        }
    }

    return true;
}

std::vector<Character> SaveSystem::getCharacters() const
{
    return {};
}

std::vector<Save> SaveSystem::getSaves(const Character& character) const
{
    return {};
}
