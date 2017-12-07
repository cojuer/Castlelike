#include "subsystem_render.h"

#include <iostream>
#include <string>

#include "animation.h"
#include "atexture.h"
#include "options.h"
#include "renderable.h"
#include "renderer.h"
#include "global_time.h"
#include "window.h"

RenderSubsystem::RenderSubsystem() = default;

RenderSubsystem::~RenderSubsystem()
{
    SDL_Quit();
}

bool RenderSubsystem::init(Options& opts)
{
    m_opts = &opts;

    if (!initSDL()) goto err1;

    if (!createWindow()) goto err2;
    m_window->configure(opts);

    if (!createRenderer()) goto err3;

    return true;

    err3:
    auto window = m_window.release();
    delete(window);
    err2:
    deinitSDL();
    err1:
    return false;
}

void RenderSubsystem::render(Renderable* obj, SDL_Rect dstrect) const
{
    if (!obj || !obj->getTexture()) return;

    auto texture = obj->getTexture()->getSDLTexture();
    auto src = obj->getTexture()->getSrcRect();
    float rotation = 0;

    if (!dstrect.w || !dstrect.h)
    {
        SDL_QueryTexture(texture, nullptr, nullptr, &dstrect.w, &dstrect.h);
    }
    SDL_RenderCopyEx(m_renderer->getSDLRenderer(), texture, &src, &dstrect, rotation, nullptr, SDL_FLIP_NONE);
}

void RenderSubsystem::render(Renderable* obj, FramedTransform* transform, SDL_Rect dstrect) const
{
    if (!obj || !obj->getTexture()) return;

    auto texture = obj->getTexture()->getSDLTexture();
    auto src = obj->getTexture()->getSrcRect();

    auto now = TimePoint{ GlobalTime::instance().getTicks() };
    float rotation = 0;
    if (transform)
    {
        dstrect.x += transform->getTransform(now).m_shift.x;
        dstrect.y += transform->getTransform(now).m_shift.y;
        rotation = transform->getTransform(now).m_angle;
    }

    if (!dstrect.w || !dstrect.h)
    {
        SDL_QueryTexture(texture, nullptr, nullptr, &dstrect.w, &dstrect.h);
    }
    SDL_RenderCopyEx(m_renderer->getSDLRenderer(), texture, &src, &dstrect, rotation, nullptr, SDL_FLIP_NONE);
}

void RenderSubsystem::clear() const
{
    SDL_RenderClear(m_renderer->getSDLRenderer());
}

void RenderSubsystem::renderPresent() const
{
    SDL_RenderPresent(m_renderer->getSDLRenderer());
}

SDL_Renderer* RenderSubsystem::getRenderer() const
{
    return m_renderer->getSDLRenderer();
}

SDL_Texture* RenderSubsystem::getSurfaceFromTexture(SDL_Surface* surface) const
{
    return SDL_CreateTextureFromSurface(m_renderer->getSDLRenderer(), surface);
}

bool RenderSubsystem::initSDL()
{
    return (SDL_Init(SDL_INIT_EVERYTHING) >= 0);
}

bool RenderSubsystem::createWindow()
{
    // FIXME: use opts?
    auto windowName = "Castlelike";
    // FIXME: 2 magic consts
    SDL_Rect geom{ 100, 100, m_opts->getInt("Width"), m_opts->getInt("Height") };
    auto sdlWindow = SDL_CreateWindow(windowName, geom.x, geom.y, geom.w, geom.h, SDL_WINDOW_SHOWN);
    if (sdlWindow)
    {
        m_window.reset(new Window(*sdlWindow));
    }
    return sdlWindow;
}

bool RenderSubsystem::createRenderer()
{
    unsigned flags = SDL_RENDERER_ACCELERATED;
    // FIXME: 1 magic const
    auto sdlRenderer = SDL_CreateRenderer(m_window->getSDLWindow(), -1, flags);
    if (sdlRenderer)
    {
        m_renderer.reset(new Renderer(*sdlRenderer));
    }
    return sdlRenderer;
}

void RenderSubsystem::deinitSDL()
{
    SDL_Quit();
}
