/* 
   Network Configurator
   
   textdisplay.cpp
   
   Copyright (C)2002,2003 Cryptic Allusion, LLC
   Donated from Feet of Fury

   $Id: textdisplay.cpp,v 1.1 2003/07/15 07:55:06 bardtx Exp $
*/

#include <tsu/font.h>
#include <plx/list.h>
#include <plx/context.h>
#include <plx/prim.h>
#include "textdisplay.h"

TextDisplay::TextDisplay(Font *fh, float ps, bool center) {
	m_fh = fh;
	assert( m_fh != NULL );

	m_text = NULL;
	m_text_len = 0;
	m_ps = ps;
	m_bga = 0.0f;
	m_center = center;
}

TextDisplay::~TextDisplay() {
}

void TextDisplay::setBGAlpha(float a) {
	m_bga = a;
}

void TextDisplay::setText(const char **text, int linecnt) {
	// Setup our basic text stuff
	m_text = text;
	m_line_cnt = linecnt;

	// Now figure out how big we'll be
	m_w = m_h = 0;
	m_text_len = 0;
	for (int i=0; i<m_line_cnt; i++) {
		float w, h;

		m_fh->setSize(m_ps);
		m_fh->getTextSize(m_text[i], &w, &h);

		if (w > m_w)
			m_w = w;
		m_h += h * 1.5f;

		m_text_len += strlen(m_text[i]);
	}

	float l, u, r, d;
	plx_fcxt_char_metrics((*m_fh), '\'',
		&l, &u, &r, &d);
}

void TextDisplay::getSize(float & w, float & h) {
	w = m_w;
	h = m_h;
}

void TextDisplay::setFont(Font *f) {
	m_fh = f;
}

void TextDisplay::setSize(float s) {
	m_ps = s;
	setText(m_text, m_line_cnt);
}

void TextDisplay::draw(int list) {
	// We only do translucent
	if (list != PLX_LIST_TR_POLY)
		return;

	// Start at the center point
	Vector pos = getPosition();
	Color col = getColor();
	if (col.r == 1.0f && col.g == 1.0f && col.b == 1.0f) {
		col.r = col.g = col.b = 0.85f;
	}

	// Move out for the proper size
	if (!m_center)
		pos.x -= m_w/2.0f;
	pos.y -= m_h/2.0f;

	m_fh->setSize(m_ps);
	m_fh->setAlpha(col.a);
	m_fh->setColor(col.r, col.g, col.b);
	for (int i=0; i<m_line_cnt; i++) {
		float tx = pos.x, ty = pos.y, sx, sy;
		m_fh->upperleftCoords(m_text[i], &tx, &ty);
		m_fh->getTextSize(m_text[i], &sx, &sy);

		if (m_center)
			tx += -sx/2.0f;

		m_fh->draw(tx, ty, pos.z, m_text[i]);
		
		pos.y += sy * 1.5f;
	}

	pos = getPosition();
	if (m_bga > 0.0f) {
		uint32 color = plx_pack_color(col.a * m_bga, 0.0f, 0.0f, 0.0f);
		plx_cxt_texture(NULL); plx_cxt_send(list);
		plx_vert_inp(PLX_VERT, pos.x - (m_w + m_ps)/2.0f, pos.y + (m_h + m_ps)/2.0f, pos.z-0.01f, color);
		plx_vert_inp(PLX_VERT, pos.x - (m_w + m_ps)/2.0f, pos.y - (m_h + m_ps)/2.0f, pos.z-0.01f, color);
		plx_vert_inp(PLX_VERT, pos.x + (m_w + m_ps)/2.0f, pos.y + (m_h + m_ps)/2.0f, pos.z-0.01f, color);
		plx_vert_inp(PLX_VERT_EOS, pos.x + (m_w + m_ps)/2.0f, pos.y - (m_h + m_ps)/2.0f, pos.z-0.01f, color);
	}
}

void TextDisplay::nextFrame() {
	Drawable::nextFrame();
}

