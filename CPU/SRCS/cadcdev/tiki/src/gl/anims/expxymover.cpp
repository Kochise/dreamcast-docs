/*
   Tiki

   expxymover.cpp

   Copyright (C)2002,2003,2004 Dan Potter
   Copyright (C)2005 Cryptic Allusion, LLC
*/

#include "pch.h"
#include "Tiki/drawable.h"
#include "Tiki/anims/expxymover.h"

using namespace Tiki::GL;

ExpXYMover::ExpXYMover(float dx, float dy, float maxx, float maxy) {
	m_dx = dx;
	m_dy = dy;
	m_maxx = maxx;
	m_maxy = maxy;
}

ExpXYMover::~ExpXYMover() { }

void ExpXYMover::nextFrame(Drawable *t, uint64 /*tm*/) {
	Vector p = t->getTranslate();
	
	bool xfin = m_dx < 0 ? (p.x <= m_maxx) : (p.x >= m_maxx);
	bool yfin = m_dy < 0 ? (p.y <= m_maxy) : (p.y >= m_maxy);
	if (xfin && yfin) {
		t->setTranslate(Vector(m_maxx, m_maxy, p.z));
		complete(t);
		return;
	}

	// Move 1.15x of the distance each frame
	p += Vector(m_dx, m_dy, 0);
	t->setTranslate(p);
	m_dx *= 1.15f;
	m_dy *= 1.15f;
}
