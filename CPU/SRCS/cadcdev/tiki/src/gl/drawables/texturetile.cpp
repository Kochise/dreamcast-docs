/*
   Tiki

   texturetile.cpp

   Copyright (C)2005 Atani Software
*/

#include "pch.h"

#include "Tiki/drawables/texturetile.h"
#include "Tiki/drawables/banner.h"
#include "Tiki/plxcompat.h"

using namespace Tiki::GL;
using namespace Tiki::GL::Plxcompat;

TextureTile::TextureTile(ObjType t, Texture * texture) : Banner(t, texture) {
}

TextureTile::~TextureTile() {
}

void TextureTile::setTileSize(float w, float h) {
	m_tile_w = w;
	m_tile_h = h;
}

void TextureTile::selectTile(float x, float y) {
	m_sel_tile_x = x;
	m_sel_tile_y = y;

	float start_x = m_tile_w * x;
	float start_y = m_tile_h * y;
	float stop_x = start_x + m_tile_w;
	float stop_y = start_y + m_tile_h;

	// select region of texture that matches the x/y coord of tile in texture
	setUV(start_x / m_texture->getW(), stop_y  / m_texture->getH(),
	      start_x / m_texture->getW(), start_y / m_texture->getH(),
	      stop_x  / m_texture->getW(), stop_y  / m_texture->getH(),
	      stop_x  / m_texture->getW(), start_y / m_texture->getH()
	     );
}
