#pragma once

#include <cstdint>
#include <memory>
#include <string>

#include "renderable.h"

class Tile
{
public:
    Tile(std::string tileset, uint32_t id, Renderable* view, bool collisive);

    uint32_t       getID() const;
    std::string    getTileset() const;
    Renderable*    getView() const;
    bool           isCollisive() const;

private:
    std::string     m_tileset;
    uint32_t        m_id;
    std::unique_ptr<Renderable> m_view;
	bool            m_collisive;
};