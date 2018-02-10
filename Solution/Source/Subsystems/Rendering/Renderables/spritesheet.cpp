#include "spritesheet.h"

#include "SDL_image.h"

#include "atexture.h"

SprSheet::SprSheet(std::vector<ATexture*>&& textures) :
    m_frames(std::move(textures))
{}

Renderable* SprSheet::clone() const
{
    return new SprSheet(*this);
}

void SprSheet::setFrame(int index)
{
    m_frame = index;
}

SprSheet::~SprSheet()
{
    free();
}

bool SprSheet::loadFromFile(const std::string& path, int width, int height, int frames, SDL_Renderer* renderer)
{
    auto loadedSurface = IMG_Load(path.c_str());
    SDL_Surface* surface{ nullptr };
    SDL_Texture* texture{ nullptr };
    SDL_Rect dst;
    m_frames.resize(frames);
    for (int i = 0; i < frames; ++i)
    {
        dst.x = 0;
        dst.y = i * height;
        dst.w = width;
        dst.h = height;
        surface = SDL_CreateRGBSurface(0, width, height, 32, 0xFF, 0xFF00, 0xFF0000, 0XFF000000);
        SDL_BlitSurface(loadedSurface, &dst, surface, nullptr);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        m_frames[i] = new ATexture(texture);
        SDL_FreeSurface(surface);
    }
    SDL_FreeSurface(loadedSurface);

    return true;
}

void SprSheet::free()
{
    for (auto& frame : m_frames)
    {
        delete(frame);
    }
}

ATexture* SprSheet::getTexture(int frame)
{
    return m_frames[frame];
}

ATexture* SprSheet::getTexture()
{
    return m_frames[m_frame];
}

const ATexture* SprSheet::getTexture() const
{
    return m_frames[m_frame];
}
