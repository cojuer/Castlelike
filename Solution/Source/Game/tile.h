#pragma once

#include <cstdint>

class Renderable;
class Tileset;

class Tile
{
public:
    Tile(Tileset* tileset, uint32_t id, Renderable* view, bool collisive);
	explicit Tile(Renderable* view = nullptr, bool collisive = false);

    uint32_t       getID() const;
    Tileset*       getTileset() const;
    Renderable*    getView() const;
    bool           isCollisive() const;

    ~Tile();

private:
    Tileset*        m_tileset;
    uint32_t        m_id;
    Renderable*     m_view;
	bool            m_collisive;
};