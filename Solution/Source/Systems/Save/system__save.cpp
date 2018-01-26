#include "system__save.h"

#include <algorithm>
#include <iostream>
#include <filesystem>
#include <iterator>

#include "subsystem_io.h"

#include "json_serializable.h"

namespace fs = std::experimental::filesystem;

const std::string SaveSystem::extension = ".json";
const std::string SaveSystem::format = "CASTLELIKE_SAVEFILE";

const std::string SaveSystem::profDirPath = "Profiles";
const std::string SaveSystem::infoFileName = "info.json";

bool SaveSystem::init()
{
    fs::path profPath(profDirPath);

    fs::directory_iterator begin(profPath);
    fs::directory_iterator end;
    
    // Discover all profile folders
    std::vector<fs::path> profDirs;
    std::copy_if(begin, end, std::back_inserter(profDirs), 
        [](const fs::path& path)
        {
            return fs::is_directory(path);
        });

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

            auto profName = profDir.filename().u8string();
            auto saveName = savePath.stem().u8string();
            auto iter = m_saves.find(profName);
            if (iter == m_saves.end())
            {
                m_saves[profName] = { Save{ saveName } };
            }
            else
            {
                iter->second.push_back(Save{ saveName });
            }
        }
    }

    return true;
}

void SaveSystem::useProfile(std::string profName)
{
    if (m_saves.find(profName) == m_saves.end())
    {
        m_saves[profName] = {};
        // TODO: create folder
    }
    m_currProfile = profName;
}

void SaveSystem::regSerializable(JSONSerializable& ser)
{
    m_serializables.push_back(&ser);
}

void SaveSystem::saveLast()
{
    assert(m_currProfile.length() != 0 && "profile not initialized");
    save(m_currProfile, "quicksave");
}

void SaveSystem::loadLast(ResourceSystem& resSystem)
{
    auto infoPath = fs::path(profDirPath) / infoFileName;
    Json lastInfo;
    *IOSubsystem::getInStream(infoPath) >> lastInfo;
    std::string profile = lastInfo.at("profile");
    std::string saveFileName = lastInfo.at("name").get<std::string>() + extension;
    
    m_currProfile = profile;

    auto savePath = fs::path(profDirPath) / profile / saveFileName;
    Json save;
    *IOSubsystem::getInStream(savePath) >> save;
    auto& body = save.at("body");
    for (auto serializable : m_serializables)
    {
        serializable->load(body.at(serializable->getStringID()), resSystem);
    }
}

void SaveSystem::save(const std::string& profile, const std::string& saveName)
{
    std::string saveFileName = saveName + extension;

    Json save;
    save["format"] = format;
    
    Json header;
    header["name"] = saveName;
    // type, version,...
    save["header"] = std::move(header);

    Json body;
    for (auto serializable : m_serializables)
    {
        body[serializable->getStringID()] = serializable->save();
    }
    save["body"] = std::move(body);

    // TODO: async
    auto savePath = fs::path(profDirPath) / profile / saveFileName;
    *IOSubsystem::getOutStream(savePath) << save;

    Json lastInfo;
    lastInfo["profile"] = profile;
    lastInfo["name"] = saveName;
    auto infoPath = fs::path(profDirPath) / infoFileName;
    *IOSubsystem::getOutStream(infoPath) << lastInfo;
}

void SaveSystem::load(const std::string& profile, const std::string& saveName, ResourceSystem& resSystem)
{
    m_currProfile = profile;

    auto savePath = fs::path(profDirPath) / profile / (saveName + extension);
    Json save;
    *IOSubsystem::getInStream(savePath) >> save;
    auto& body = save.at("body");
    for (auto serializable : m_serializables)
    {
        serializable->load(body.at(serializable->getStringID()), resSystem);
    }
}

const Profile& SaveSystem::getCurrProfile() const
{
    return m_currProfile;
}

std::vector<Profile> SaveSystem::getProfiles() const
{
    std::vector<Profile> result;
    for (auto& [profile, saves] : m_saves)
    {
        result.push_back(profile);
    }
    return result;
}

std::vector<Save> SaveSystem::getSaves(const Profile& profile) const
{
    auto iter = m_saves.find(profile);
    return iter != m_saves.end() ? iter->second : std::vector<Save>{};
}
