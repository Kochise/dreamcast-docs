/* 
   Network Configurator
      
   drawables/menubox.cc
   
   Copyright (C)2003 Cryptic Allusion, LLC
   Donated from Feet of Fury

   $Id: menubox.cpp,v 1.1 2003/07/15 07:55:06 bardtx Exp $
*/

#include <plx/prim.h>
#include <plx/list.h>
#include <plx/context.h>
#include "menubox.h"
#include "hsv.h"

MenuBox::MenuBox(bool border) {
	m_border = border;
	m_frame = 0;
}

MenuBox::~MenuBox() {
}

void MenuBox::draw(int list) {
	Drawable::draw(list);
	if (list != PLX_LIST_TR_POLY)
		return;

	plx_dr_state_t dr;
	plx_dr_init(&dr);

	// No textures needed
	plx_cxt_texture(NULL);
	plx_cxt_culling(PLX_CULL_NONE);
	plx_cxt_send(list);

	Vector t = getPosition();
	Vector s = getScale();		// scale == usable interior size here
	Color col = getColor();

	// We only want the "radius" of the box, not diameter.
	s.x = s.x/2;
	s.y = s.y/2;

	if (m_border) {
		// Draw the frame itself, a bit in front of our official Z
		uint32 mcol1 = plx_pack_color(col.a, col.r*0.3f, col.g*0.3f, col.b*0.3f),
			mcol2 = plx_pack_color(col.a, col.r*0.7f, col.g*0.7f, col.b*0.7f);

		// Left side
		plx_vert_ind(&dr, PLX_VERT, t.x-(s.x+6), t.y+(s.y+6), t.z+0.001f, mcol1);
		plx_vert_ind(&dr, PLX_VERT, t.x-(s.x+6), t.y-(s.y+6), t.z+0.001f, mcol1);
		plx_vert_ind(&dr, PLX_VERT, t.x-(s.x+3), t.y+(s.y+3), t.z+0.001f, mcol2);
		plx_vert_ind(&dr, PLX_VERT, t.x-(s.x+3), t.y-(s.y+3), t.z+0.001f, mcol2);
		plx_vert_ind(&dr, PLX_VERT, t.x-(s.x+0), t.y+(s.y+0), t.z+0.001f, mcol1);
		plx_vert_ind(&dr, PLX_VERT_EOS, t.x-(s.x+0), t.y-(s.y+0), t.z+0.001f, mcol1);

		// Top side
		plx_vert_ind(&dr, PLX_VERT, t.x-(s.x+6), t.y-(s.y+6), t.z+0.001f, mcol1);
		plx_vert_ind(&dr, PLX_VERT, t.x+(s.x+6), t.y-(s.y+6), t.z+0.001f, mcol1);
		plx_vert_ind(&dr, PLX_VERT, t.x-(s.x+3), t.y-(s.y+3), t.z+0.001f, mcol2);
		plx_vert_ind(&dr, PLX_VERT, t.x+(s.x+3), t.y-(s.y+3), t.z+0.001f, mcol2);
		plx_vert_ind(&dr, PLX_VERT, t.x-(s.x+0), t.y-(s.y+0), t.z+0.001f, mcol1);
		plx_vert_ind(&dr, PLX_VERT_EOS, t.x+(s.x+0), t.y-(s.y+0), t.z+0.001f, mcol1);

		// Right side
		plx_vert_ind(&dr, PLX_VERT, t.x+(s.x+0), t.y+(s.y+0), t.z+0.001f, mcol1);
		plx_vert_ind(&dr, PLX_VERT, t.x+(s.x+0), t.y-(s.y+0), t.z+0.001f, mcol1);
		plx_vert_ind(&dr, PLX_VERT, t.x+(s.x+3), t.y+(s.y+3), t.z+0.001f, mcol2);
		plx_vert_ind(&dr, PLX_VERT, t.x+(s.x+3), t.y-(s.y+3), t.z+0.001f, mcol2);
		plx_vert_ind(&dr, PLX_VERT, t.x+(s.x+6), t.y+(s.y+6), t.z+0.001f, mcol1);
		plx_vert_ind(&dr, PLX_VERT_EOS, t.x+(s.x+6), t.y-(s.y+6), t.z+0.001f, mcol1);

		// Bottom side
		plx_vert_ind(&dr, PLX_VERT, t.x-(s.x+0), t.y+(s.y+0), t.z+0.001f, mcol1);
		plx_vert_ind(&dr, PLX_VERT, t.x+(s.x+0), t.y+(s.y+0), t.z+0.001f, mcol1);
		plx_vert_ind(&dr, PLX_VERT, t.x-(s.x+3), t.y+(s.y+3), t.z+0.001f, mcol2);
		plx_vert_ind(&dr, PLX_VERT, t.x+(s.x+3), t.y+(s.y+3), t.z+0.001f, mcol2);
		plx_vert_ind(&dr, PLX_VERT, t.x-(s.x+6), t.y+(s.y+6), t.z+0.001f, mcol1);
		plx_vert_ind(&dr, PLX_VERT_EOS, t.x+(s.x+6), t.y+(s.y+6), t.z+0.001f, mcol1);
	}

	// Finally, the actual menu background itself
	float	phase = 1.0f * (m_frame % (60*4)) / (60*4);
	uint32	color;
	float	r, g, b;
	
	hsvSpectrum(phase+0.75f, r, g, b); color = plx_pack_color(col.a * 0.9f, col.r*r * 0.3f, col.g*g * 0.3f, col.b*b * 0.3f);
	plx_vert_ind(&dr, PLX_VERT, t.x-s.x, t.y+s.y, t.z, color);
	hsvSpectrum(phase+0.00f, r, g, b); color = plx_pack_color(col.a * 0.9f, col.r*r * 0.3f, col.g*g * 0.3f, col.b*b * 0.3f);
	plx_vert_ind(&dr, PLX_VERT, t.x-s.x, t.y-s.y, t.z, color);
	hsvSpectrum(phase+0.50f, r, g, b); color = plx_pack_color(col.a * 0.9f, col.r*r * 0.3f, col.g*g * 0.3f, col.b*b * 0.3f);
	plx_vert_ind(&dr, PLX_VERT, t.x+s.x, t.y+s.y, t.z, color);
	hsvSpectrum(phase+0.25f, r, g, b); color = plx_pack_color(col.a * 0.9f, col.r*r * 0.3f, col.g*g * 0.3f, col.b*b * 0.3f);
	plx_vert_ind(&dr, PLX_VERT_EOS, t.x+s.x, t.y-s.y, t.z, color);
}

void MenuBox::nextFrame() {
	Drawable::nextFrame();
	m_frame++;
}

