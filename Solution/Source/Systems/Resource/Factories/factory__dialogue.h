#pragma once

#include <memory>

#include "dialogue.h"
#include "factory.h"

class JsonLoader;
class DialogueParser;

class DialFactory : Factory<Dialogue>
{
public:
    DialFactory();

    bool          load(const std::string& fname) override;
    Resource<Dialogue>* get(ResourceId& id) override;

private:
    std::unique_ptr<JsonLoader>     m_loader;
    std::unique_ptr<DialogueParser> m_parser;
};
