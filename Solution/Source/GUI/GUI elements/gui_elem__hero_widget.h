#pragma once

#include "widget.h"

class Actor;
class ResourceSystem;
class GameSystemManager;

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

    void             init(ResourceSystem& resSystem, Actor& hero);
};

} /* gui namespace. */
