#include "loader__renderable.h"

#include <iostream>

#include "system__resource.h"
#include "spritesheet.h"
#include "text_renderer.h"
#include "color.h"

RenderableLoader::RenderableLoader() : 
    m_resSystem(nullptr), 
    m_rendSubsystem(nullptr)
{}

bool RenderableLoader::init(ResourceSystem& resSystem, RenderSubsystem& rendSubsystem)
{
    m_resSystem = &resSystem;
    m_rendSubsystem = &rendSubsystem;
    return true;
}

bool RenderableLoader::load(const std::string& fname)
{
    auto result = m_parseResult.load_file(fname.c_str());

    if (result)
    {
        std::cout << "Renderable loader: " << fname << " successfully loaded" << std::endl;
        return true;
    }
    return false;
}

bool RenderableLoader::has(ResourceId& id)
{
    return false;
}

Renderable* RenderableLoader::get(ResourceId& id)
{
    auto item = m_parseResult.child("rendDB").find_child_by_attribute("id", id.c_str());
    auto type = std::string(item.attribute("type").as_string());
    if (type == "img")       return getTexture(item);
    else if (type == "text") return getSprSheet(item);
	else return nullptr;
}

Renderable* RenderableLoader::getTexture(PugiNode& node) const
{
    auto& texture = *new ATexture();
    auto path = std::string("Assets\\Images\\") + std::string(node.attribute("path").as_string());
    texture.loadFromFile(path, *m_rendSubsystem);
    return &texture;
}
// TODO: rewrite
Renderable* RenderableLoader::getAnimation(PugiNode& node) const
{
    auto& texture = *new ATexture();
    return &texture;
}

Renderable* RenderableLoader::getSprSheet(PugiNode& node) const
{
    auto& textures = *new std::vector<ATexture*>(node.attribute("frames").as_int());
    int counter = 0;
    for (PugiNode frame = node.child("frame"); frame; frame = frame.next_sibling("frame"))
    {
        std::string text = frame.attribute("text").as_string();
        std::string fName = frame.attribute("font").as_string();
        int fSize = frame.attribute("size").as_int();
        uint8_t r = frame.attribute("r").as_int();
        uint8_t g = frame.attribute("g").as_int();
        uint8_t b = frame.attribute("b").as_int();
        Color color{ r, g, b };
        textures[counter++] = m_resSystem->textRenderer->renderTexture(text, fName, fSize, color);
    }
    auto spr = new SprSheet(textures);
    return spr;
}
