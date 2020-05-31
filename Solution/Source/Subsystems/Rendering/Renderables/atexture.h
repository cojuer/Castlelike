#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

#include "renderable.h"

class RenderSubsystem;

class ATexture : public Renderable
{
public:
    ATexture();
    explicit ATexture(SDL_Texture* texture);

    Renderable*      clone() const override;

    // FIXME: not everyone should have access to this methods
    bool             loadFromFile(const std::string& path, RenderSubsystem& rendSubsystem);
    bool             loadFromFile(const std::string& path, RenderSubsystem& rendSubsystem, SDL_Rect rect);
    bool             loadFromText(RenderSubsystem& rendSubsystem, const std::string& text, TTF_Font* font, SDL_Color color, int textWidth = 0);

	void             setSrcRect(SDL_Rect srcRect);
	void             setWidth(int width);
	void             setHeight(int height);

    SDL_Texture*     getSDLTexture() const;
    ATexture*        getTexture() override;
    const ATexture*  getTexture() const override;
    int              getWidth() const override;
    int              getHeight() const override;
	SDL_Rect         getSrcRect() const;

    ~ATexture();

private:
	SDL_Texture*     m_texture { nullptr };
	SDL_Rect         m_source { 0, 0, 0, 0 };
};