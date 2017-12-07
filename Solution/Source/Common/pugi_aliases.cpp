#include "pugi_aliases.h"

int getIntAttr(PugiNode& node, const std::string& attr)
{
    return node.attribute(attr.c_str()).as_int();
}

std::string getStrAttr(PugiNode& node, const std::string& attr)
{
    return node.attribute(attr.c_str()).as_string();
}