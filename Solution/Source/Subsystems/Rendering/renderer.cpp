#include "renderer.h"

Renderer::Renderer(SDL_Renderer& renderer) :
    m_renderer(&renderer)
{}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(m_renderer);
}

SDL_Renderer* Renderer::getSDLRenderer() const
{
    return m_renderer;
}
