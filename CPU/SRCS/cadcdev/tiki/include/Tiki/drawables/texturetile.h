/*
   Tiki

   tilemap.h

   Copyright (C)2005 Atani Software
*/

#ifndef __TIKI_DRW_TXRTILE_H
#define __TIKI_DRW_TXRTILE_H

#include "Tiki/drawable.h"
#include "Tiki/drawables/banner.h"
#include "Tiki/texture.h"
#include "Tiki/color.h"

namespace Tiki {
namespace GL {

/**
 * TileMap -- Renders a portion of texture as a tile
 */
class TextureTile : public Banner {
public:
	TextureTile(ObjType t, Texture * texture);
	virtual ~TextureTile();

	void setTileSize(float w, float h);
	void selectTile(float x, float y);

private:
	float	m_tile_w, m_tile_h;
	float	m_sel_tile_x, m_sel_tile_y;
};

};
};

#endif	// __TIKI_DRW_TXRTILE_H

