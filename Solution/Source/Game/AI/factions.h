#pragma once

#include <map>
#include <vector>

#include "pugi_aliases.h"

class Actor;

using Factions = std::vector<std::string>;
using Relations = std::map<std::pair<std::string, std::string>, int>;

/**
 * \brief Faction manager loads, parses and stores list of factions and 
 *        relations between factions 
 */
class FactionsMgr
{
public:
    static constexpr auto fearHBound    = -151;
    static constexpr auto hateLBound    = -150;
    static constexpr auto hateHBound    = -51;
    static constexpr auto neutralLBound = -50;
    static constexpr auto neutralHBound = 49;
    static constexpr auto loveLBound    = 50;
    static constexpr auto minRelation   = -200;
    static constexpr auto maxRelation   = 100;

    /**
     * \brief Loads and parses XML factions database.
     * \param fname XML database path.
     */
    void load(const std::string& fname);

    /**
     * \brief Request fst to snd relation based on all active
     *        (non-zero) relations between factions of these 
     *        actors.
     * \param fst Actor whose relations we request
     * \param snd Target of relations
     * \return Integer value of relations
     */
    int getRelation(const Actor& fst, const Actor& snd) const;


    /**
     * \brief Request constant map of relations between 
     *        different factions. If pair of factions isn't in
     *        return value, their relations value is 0(neutral).
     * \return Map with pairs of factions(means relation of 
     *         first pair faction to the second) and integer
     *         values of relations.
     */
    const Relations& getRelations() const;

private:
    Factions  factions;
    Relations relations;
    PugiDoc   parsedData;
};