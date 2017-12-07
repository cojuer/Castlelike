#pragma once

#include "widget.h"

class ResourceManager;
class SystemManager;

namespace gui {

class HeroPanel : public Widget
{
public:
    HeroPanel(const std::string& name, 
              Widget* parent,
              int x,
              int y,
              int width,
              int height,
              bool visible,
              Renderable* backImage = nullptr);

    void             init(ResourceManager& resManager, SystemManager& sysManager);
};

} /* gui namespace. */
