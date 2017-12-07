#include "renderable.h"

#include "atexture.h"

int Renderable::getWidth() const
{
    return getTexture()->getWidth();
}

int Renderable::getHeight() const
{
    return getTexture()->getHeight();
}
