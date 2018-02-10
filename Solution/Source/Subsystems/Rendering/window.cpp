#include "window.h"

#include "options.h"

Window::Window(SDL_Window& window) :
    m_window(&window)
{}

Window::~Window()
{
    SDL_DestroyWindow(m_window);
}

void Window::configure(Options& opts)
{
    if (opts.get<bool>("Fullscreen"))
    {
        SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    }
    SDL_ShowCursor(SDL_DISABLE);
}

SDL_Window* Window::getSDLWindow() const
{
    return m_window;
}
