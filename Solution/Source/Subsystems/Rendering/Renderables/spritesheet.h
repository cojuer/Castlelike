#pragma once

#include <vector>

#include <SDL.h>

#include "renderable.h"

class ATexture;

class SprSheet : public Renderable
{
public:
    SprSheet() = default;
    explicit SprSheet(std::vector<ATexture*>&& textures);

    Renderable*      clone() const override;

    void             setFrame(int index);

    ATexture*        getTexture(int frame);
    ATexture*        getTexture() override;
    const ATexture*  getTexture() const override;

    // FIXME: use JSON to initialize
    bool             loadFromFile(std::string path, int width, int height, int frames, SDL_Renderer* const renderer);

    void             free();

    ~SprSheet();

private:
    std::vector<ATexture*> m_frames;
    int                    m_frame;
};