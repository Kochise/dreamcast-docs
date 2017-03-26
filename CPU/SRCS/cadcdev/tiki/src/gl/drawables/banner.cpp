/*
   Tiki

   font.cpp

   Copyright (C)2002,2003,2004 Dan Potter
   Copyright (C)2005 Cryptic Allusion, LLC
*/

#include "pch.h"

#include "Tiki/drawables/banner.h"
#include "Tiki/plxcompat.h"

using namespace Tiki::GL;
using namespace Tiki::GL::Plxcompat;

Banner::Banner(ObjType t, Texture * texture) {
	m_list = t;
	m_texture = texture;
		
	m_u1 = m_v2 = 0.0f;
	m_u2 = m_v4 = 0.0f;
	m_u3 = m_v1 = 1.0f;
	m_u4 = m_v3 = 1.0f;
	m_w = m_h = -1.0f;
}

Banner::~Banner() {
}

void Banner::setTexture(Texture * txr) {
	m_texture = txr;
}

void Banner::setUV(float u1, float v1, float u2, float v2, float u3, float v3, float u4, float v4) {
	m_u1 = u1;
	m_v1 = v1;
	m_u2 = u2;
	m_v2 = v2;
	m_u3 = u3;
	m_v3 = v3;
	m_u4 = u4;
	m_v4 = v4;
}

void Banner::setSize(float w, float h) {
	m_w = w;
	m_h = h;
}

void Banner::draw(ObjType list) {
	if (list != m_list || !m_texture)
		return;

	m_texture->select();

	float w, h;
	if (m_w != -1 && m_h != -1) {
		w = m_w;
		h = m_h;
	} else {
		w = (float)m_texture->getW();
		h = (float)m_texture->getH();
	}

	const Vector & sv = getScale();
	w *= sv.x;
	h *= sv.y;

	const Vector & tv = getPosition();

	plx_vertex_t vert;
	if (list == Trans) {
		vert.argb = getColor();
	} else {
		Color t = getColor(); t.a = 1.0f;
		vert.argb = t;
	}
	vert.oargb = 0;

	vert.flags = PLX_VERT;
	vert.x = tv.x-w/2;
	vert.y = tv.y+h/2;
	vert.z = tv.z;
	vert.u = m_u1;
	vert.v = m_v1;
	plx_prim(&vert, sizeof(vert));

	vert.y = tv.y-h/2;
	vert.u = m_u2;
	vert.v = m_v2;
	plx_prim(&vert, sizeof(vert));

	vert.x = tv.x+w/2;
	vert.y = tv.y+h/2;
	vert.u = m_u3;
	vert.v = m_v3;
	plx_prim(&vert, sizeof(vert));

	vert.flags = PLX_VERT_EOS;
	vert.y = tv.y-h/2;
	vert.u = m_u4;
	vert.v = m_v4;
	plx_prim(&vert, sizeof(vert));
}

