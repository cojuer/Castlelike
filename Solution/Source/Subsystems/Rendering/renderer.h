#pragma once

#include <SDL.h>

class Options;

class Renderer final
{
public:
    explicit Renderer(SDL_Renderer& renderer);
    ~Renderer();

    SDL_Renderer* getSDLRenderer() const;

private:
    SDL_Renderer* m_renderer;
};
