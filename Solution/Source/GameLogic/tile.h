#pragma once

class Renderable;

class Tile
{
public:
	explicit Tile(Renderable* view = nullptr, bool collisive = false);

    Renderable*    getView() const;
    bool           isCollisive() const;

private:
    Renderable*     m_view;
	bool            m_collisive;
};