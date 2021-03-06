#pragma once

#include "widget.h"

namespace gui {

class NumberWidget : public Widget
{
public:
    NumberWidget(const std::string& name, Widget* parent, SDL_Rect geometry, bool visible, const int* number);

    void setData(const int& number);
    void eraseData();

    void render(RenderSubsystem& rendSubsys, ResourceSystem& resSystem, Vec2i coordStart) const override;

private:
    const int* m_number;
};

} /* gui namespace. */