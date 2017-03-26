/*
 Tiki
 
 pointerArrow.cpp
 
 Copyright (C)2005 Sam Steele
 */

#include "pch.h"

#include "Tiki/texture.h"
#include "Tiki/plxcompat.h"
#include "Tiki/drawables/pointerArrow.h"

using namespace Tiki::GL;
using namespace Tiki::GL::Plxcompat;

PointerArrow::PointerArrow() {
	setTint(Color(1.0,0.2,0.1));
}

PointerArrow::~PointerArrow() {
}

void PointerArrow::draw(ObjType list) {
	plx_vertex_t vert;
	const Vector & tv = getPosition();

	Texture::deselect();
	
	if(list==Trans) {
		vert.argb = Color(0,0,0);
		vert.z = tv.z;
		
		vert.flags = PLX_VERT;
		vert.x = tv.x-2;
		vert.y = tv.y-4;
		plx_prim(&vert, sizeof(vert));
		
		vert.flags = PLX_VERT;
		vert.x = tv.x+18;
		vert.y = tv.y+16;
		plx_prim(&vert, sizeof(vert));
		
		vert.flags = PLX_VERT_EOS;
		vert.x = tv.x-2;
		vert.y = tv.y+24;
		plx_prim(&vert, sizeof(vert));
		
		vert.argb = getTint();
		vert.z = tv.z + 0.01;
		
		vert.flags = PLX_VERT;
		vert.x = tv.x;
		vert.y = tv.y;
		plx_prim(&vert, sizeof(vert));
		
		vert.flags = PLX_VERT;
		vert.x = tv.x+15;
		vert.y = tv.y+15;
		plx_prim(&vert, sizeof(vert));
		
		vert.flags = PLX_VERT_EOS;
		vert.x = tv.x;
		vert.y = tv.y+21;
		plx_prim(&vert, sizeof(vert));
	}
}
