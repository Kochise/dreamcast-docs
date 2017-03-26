/*
   Tsunami for KallistiOS ##version##

   expxymover.cpp

   (c)2002 Dan Potter
*/

#include <tsu/drawable.h>
#include <tsu/anims/expxymover.h>

CVSID("$Id: expxymover.cpp,v 1.1 2002/09/09 08:43:37 bardtx Exp $");

ExpXYMover::ExpXYMover(float dx, float dy, float maxx, float maxy) {
	m_dx = dx;
	m_dy = dy;
	m_maxx = maxx;
	m_maxy = maxy;
}

ExpXYMover::~ExpXYMover() { }

void ExpXYMover::nextFrame(Drawable *t) {
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
