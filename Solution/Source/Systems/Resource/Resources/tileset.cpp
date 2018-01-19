#include "tileset.h"

#include "tile.h"

Tileset::Tileset(ResourceId id) :
    m_resID(id)
{}

Tile* Tileset::getTile(uint32_t id)
{
    auto view = new ATexture(*m_image);
    auto x = m_margin + id % m_cols * (m_tileW + m_spacing);
    auto y = m_margin + id / m_cols * (m_tileH + m_spacing);
    SDL_Rect src{ x, y, m_tileW, m_tileH };
    view->setSrcRect(src);
    return new Tile{ this, id, view, m_terrains.at(m_tileTerrs.at(id)).m_collisive };
}