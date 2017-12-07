#pragma once

class Renderable;

struct Tileset
{
	Renderable* m_image;
	int m_margin;
	int m_spacing;
	int m_firstgid;
	int m_columns;
	int m_tileWidth;
	int m_tileHeight;
};