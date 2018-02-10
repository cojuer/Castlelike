#pragma once

#include <SDL.h>

class Options;

class Renderer final
{
public:
    explicit Renderer(SDL_Renderer& renderer);

    Renderer(const Renderer&) = delete;
    Renderer(Renderer&&) = delete;
    Renderer& operator=(const Renderer&) = delete;
    Renderer& operator=(Renderer&&) = delete;

    ~Renderer();

    SDL_Renderer* getSDLRenderer() const;

private:
    SDL_Renderer* m_renderer;
};
