#include "widget__progress_bar.h"

#include "atexture.h"
#include "renderable.h"
#include "system__resource.h"
#include "subsystem__render.h"

namespace gui {

ProgressBar::ProgressBar(Widget* parent) :
    Widget(parent), 
    m_progress(nullptr), 
    m_max(nullptr)
{}

void ProgressBar::setData(const int& progress, const int& max)
{
    m_progress = &progress;
    m_max      = &max;
}

void ProgressBar::render(RenderSubsystem& rendSubsystem, 
                         ResourceSystem& resSystem,
                         Vec2i coordStart) const
{
    if (!m_visible) return;

    int rendWidth = static_cast<int>(m_geometry.w * (1.0 * (*m_progress) / (*m_max)));
	SDL_Rect srcRect = { 0, 0, rendWidth, m_geometry.h };
	m_rendered->getTexture()->setSrcRect(srcRect);
	SDL_Rect dstRect = { m_geometry.x + coordStart.x,
						 m_geometry.y + coordStart.y, 
						 rendWidth, m_geometry.h };
    rendSubsystem.render(m_rendered, dstRect);
}

} /* gui namespace. */