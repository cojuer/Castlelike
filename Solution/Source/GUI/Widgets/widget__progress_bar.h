#pragma once

#include "widget.h"

class Renderable;

namespace gui {

class ProgressBar : public Widget
{
public:
    explicit ProgressBar(Widget* parent = nullptr);

    void setData(const int& progress, const int& max);

    void render(RenderSubsystem& rendSubsystem, ResourceSystem& resSystem, Vec2i coordStart = { 0, 0 }) const override;

private:
    const int*       m_progress;
    const int*       m_max;
};

} /* gui namespace. */