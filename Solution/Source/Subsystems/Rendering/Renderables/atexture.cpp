#include "atexture.h"

#include <SDL_image.h>

#include "subsystem__render.h"

ATexture::ATexture() = default;

ATexture::ATexture(SDL_Texture* texture) :
    m_texture(texture),
    m_source({ 0,0,0,0 })
{
    SDL_QueryTexture(texture, nullptr, nullptr, &m_source.w, &m_source.h);
}

Renderable* ATexture::clone() const
{
    return new ATexture(*this);
}

bool ATexture::loadFromFile(std::string path, RenderSubsystem& rendSubsystem)
{
    auto loadedSurface = IMG_Load(path.c_str());
    auto texture = rendSubsystem.getSurfaceFromTexture(loadedSurface);
    SDL_FreeSurface(loadedSurface);
    this->m_texture = texture;
    SDL_QueryTexture(texture, nullptr, nullptr, &m_source.w, &m_source.h);
    return (texture != nullptr);
}

bool ATexture::loadFromText(RenderSubsystem& rendSubsystem, std::string text, TTF_Font* font, SDL_Color color, int textWidth)
{
    SDL_Surface* surface = nullptr;
    if (textWidth > 0)
    {
        surface = TTF_RenderText_Blended_Wrapped(font, text.c_str(), color, textWidth);
    }
    else
    {
        surface = TTF_RenderText_Blended(font, text.c_str(), color);
    }
    m_texture = rendSubsystem.getSurfaceFromTexture(surface);
    SDL_QueryTexture(m_texture, nullptr, nullptr, &m_source.w, &m_source.h);
    SDL_FreeSurface(surface);
    return (m_texture != nullptr);
}

void ATexture::setSrcRect(SDL_Rect srcRect)
{
	this->m_source = srcRect;
}

void ATexture::setWidth(int width)
{
	m_source.w = width;
}

void ATexture::setHeight(int height)
{
	m_source.h = height;
}

SDL_Texture* ATexture::getSDLTexture() const
{
    return m_texture;
}

ATexture* ATexture::getTexture()
{
    return this;
}

const ATexture* ATexture::getTexture() const
{
    return this;
}

int ATexture::getWidth() const
{
    return m_source.w;
}

int ATexture::getHeight() const
{
    return m_source.h;
}

SDL_Rect ATexture::getSrcRect() const
{
	return m_source;
}

ATexture::~ATexture()
{
    //if (m_texture != nullptr)
    //{
    //    SDL_DestroyTexture(m_texture);
    //}
}