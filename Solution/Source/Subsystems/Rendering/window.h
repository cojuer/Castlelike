#pragma once

#include <SDL.h>

class Options;

class Window final
{
public:
    explicit Window(SDL_Window& window);

    Window(const Window&) = delete;
    Window(Window&&) = delete;
    Window& operator=(const Window&) = delete;
    Window& operator=(Window&&) = delete;

    ~Window();
    
    void configure(Options& opts);

    SDL_Window* getSDLWindow() const;

private:
    SDL_Window* m_window;
};
