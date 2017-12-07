#include "factions.h"

#include <iostream>

#include "actor.h"
#include "utils.h"

void FactionsMgr::load(const std::string& fname)
{
    parsedData.load_file(fname.c_str());
    auto db = parsedData.child("factionsDB");

    for (auto faction = db.child("faction"); faction; faction = faction.next_sibling("faction"))
    {
        factions.push_back(faction.attribute("name").as_string());
    }
    for (auto rel = db.child("relation"); rel; rel = rel.next_sibling("relation"))
    {
        auto fst = std::string(rel.attribute("a").as_string());
        auto snd = std::string(rel.attribute("b").as_string());
        utils::logassert(std::count(factions.begin(), factions.end(), fst), "incorrect faction");
        utils::logassert(std::count(factions.begin(), factions.end(), snd), "incorrect faction");
        auto val = rel.attribute("val").as_int();
        relations[{fst, snd}] = val;
        std::cout << fst << "->" << val << "->" << snd << std::endl;
    }
}

int FactionsMgr::getRelation(const Actor& fst, const Actor& snd) const
{
    // FIXME: rewrite for actors
   /* const auto& fstChar = dcast<const CreatureActor&>(fst);
    const auto& sndChar = dcast<const CreatureActor&>(snd);

    const auto& fstFactions = fstChar.getBehaviour().getFactions();
    const auto& sndFactions = sndChar.getBehaviour().getFactions();

    auto activeRelations = 0;
    auto relation = 0;
    for (auto& fstFact : fstFactions)
    {
        for (auto& sndFact : sndFactions)
        {
            auto iter = relations.find({ fstFact, sndFact });
            if (iter != relations.end())
            {
                ++activeRelations;
                relation += (*iter).second;
            }
        }
    }
    relation /= activeRelations;
    return relation;*/
    return 0;
}

const Relations& FactionsMgr::getRelations() const
{
    return relations;
}