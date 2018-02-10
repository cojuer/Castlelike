#pragma once

#include <SDL.h>
#include <memory>

class FramedTransform;
class Options;
class Renderable;
class Renderer;
class Window;

class RenderSubsystem final
{
public:
    RenderSubsystem();

    RenderSubsystem(const RenderSubsystem&) = delete;
    RenderSubsystem(RenderSubsystem&&) = delete;
    RenderSubsystem& operator=(const RenderSubsystem&) = delete;
    RenderSubsystem& operator=(RenderSubsystem&&) = delete;

    ~RenderSubsystem();

    bool init(Options& opts);

    void render(Renderable* obj, SDL_Rect dstrect) const;
    void render(Renderable* obj, FramedTransform* transform, SDL_Rect dstrect) const;

    void clear() const;
    void renderPresent() const;

    SDL_Renderer* getRenderer() const;
    SDL_Texture* getSurfaceFromTexture(SDL_Surface* surface) const;

private:
    bool initSDL();
    bool createWindow();
    bool createRenderer();

    void deinitSDL();

private:
    Options*      m_opts { nullptr };

    std::unique_ptr<Renderer> m_renderer;
    std::unique_ptr<Window>   m_window;
};