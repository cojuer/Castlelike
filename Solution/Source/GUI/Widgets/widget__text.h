#pragma once

#include "widget.h"
#include "color.h"

namespace gui {

// FIXME: rewrite or delete
class TextWidget : public Widget
{
public:
    TextWidget(const std::string& name, 
               Widget* parent,
               SDL_Rect geometry,
               bool visible,
               const std::string& fName,
               int fSize,
               Color color,
               const std::string* textS);

    void render(RenderSubsystem& rendSubsys,
                ResourceSystem& resSystem,
                Vec2i coordStart) const override;

private:
    // FIXME: codestyle
    std::string     fName;
    int             fSize;
    Color          color;
    const std::string* text;
};

} /* gui namespace. */
