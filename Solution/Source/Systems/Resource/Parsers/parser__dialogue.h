#pragma once

#include "dialogue.h"
#include "parser__json.h"

class ResourceSystem;

class DialogueParser : public JsonParser<Dialogue*>
{
public:
    Dialogue* parse(const std::string& nodeName, Json& node) override;
};