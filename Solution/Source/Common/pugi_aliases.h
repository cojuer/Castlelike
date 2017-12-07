#pragma once

#include "pugixml.hpp"

using PugiDoc    = pugi::xml_document;
using PugiNode   = pugi::xml_node;
using PugiAttr   = pugi::xml_attribute;

int         getIntAttr(PugiNode& node, const std::string& attr);
std::string getStrAttr(PugiNode& node, const std::string& attr);