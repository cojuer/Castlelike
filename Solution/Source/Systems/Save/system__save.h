#pragma once

#include <string>
#include <map>
#include <vector>

class ResourceSystem;
class JSONSerializable;

using Profile = std::string;

struct Save
{
    std::string name;
    // date
    // play time
};

class SaveSystem
{
    static const std::string extension;
    static const std::string format;

    static const std::string profDirPath;
    static const std::string infoFileName;

public:
    bool init();

    void useProfile(std::string profName);
    void regSerializable(JSONSerializable& ser);

    void saveLast();
    void loadLast(ResourceSystem& resSystem);
    void save(const std::string& profile, const std::string& saveName);
    void load(const std::string& profile, const std::string& saveName, ResourceSystem& resSystem);

    const Profile&       getCurrProfile() const;
    std::vector<Profile> getProfiles() const;
    std::vector<Save>    getSaves(const Profile& profile) const;

private:
    Profile m_currProfile;
    std::map<Profile, std::vector<Save>> m_saves;

    std::vector<JSONSerializable*> m_serializables;
};