#include "parser__dialogue.h"

Dialogue* DialogueParser::parse(const std::string& nodeName, Json& node)
{
    auto res = new Dialogue();
    auto& states = node["states"];
    for (auto& state : states)
    {
        DialState dState;
        auto& phrases = state["phrases"];
        for (auto& phrase : phrases)
        {
            DialPhrase dPhrase;
            dPhrase.actor = phrase["actor"].get<std::string>();
            //dPhrase.condition = phrase["condition"].get<std::string>();
            //dPhrase.action = phrase["action"].get<std::string>();
            dPhrase.nextState = phrase["goto"].is_null() ? -1 : phrase["goto"].get<int32_t>();
            dPhrase.text = phrase["text"].get<std::string>();
            dState.phrases.push_back(dPhrase);
        }
        auto& answers = state["answers"];
        for (auto& answer : answers)
        {
            DialAnswer dAnswer;
            dAnswer.actor = answer["actor"].get<std::string>();
            //dAnswer.condition = answer["condition"].get<std::string>();
            //dAnswer.action = answer["action"].get<std::string>();
            dAnswer.nextState = answer["goto"].is_null() ? -1 : answer["goto"].get<int32_t>();
            dAnswer.text = answer["text"].get<std::string>();
            dState.answers.push_back(dAnswer);
        }
        res->states.push_back(dState);
    }
    return res;
}