#pragma once

#include <vector>

static constexpr auto dialMaxAnswers = 6;

struct DialPhrase;
struct DialAnswer;

struct DialState
{
    using Phrases = std::vector<DialPhrase>;
    using Answers = std::vector<DialAnswer>;

    Phrases phrases;
    Answers answers;
};

struct DialPhrase
{
    std::string      actor;
    std::string      condition;
    std::string      text;
    std::string      action;
    int              nextState;
};

struct DialAnswer
{
    std::string      actor;
    std::string      condition;
    std::string      text;
    std::string      action;
    int              nextState;
};

struct Dialogue
{
    std::vector<std::string> actors;
    std::vector<DialState> states;
};