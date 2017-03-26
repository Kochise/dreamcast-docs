/*
   Tiki

   logxymover.cpp

   Copyright (C)2002,2003,2004 Dan Potter
   Copyright (C)2005 Cryptic Allusion, LLC
*/

#include "pch.h"
#include "Tiki/anims/logxymover.h"
#include <math.h>
#include <assert.h>

using namespace Tiki::GL;

LogXYMover::LogXYMover(float dstx, float dsty, float divisor) {
	m_dstx = dstx;
	m_dsty = dsty;
	m_div = divisor;
	
	assert( m_div );
}

LogXYMover::~LogXYMover() { }

void LogXYMover::nextFrame(Drawable *t, uint64 /*tm*/) {
	Vector pos = t->getTranslate();
	if (fabs(pos.x - m_dstx) < 1.0f && fabs(pos.y - m_dsty) < 1.0f) {
		t->setTranslate(Vector(m_dstx, m_dsty, pos.z));
		complete(t);
	} else {
		// Move 1/8 of the distance each frame
		float dx = m_dstx - pos.x;
		float dy = m_dsty - pos.y;
		t->setTranslate(Vector(
			pos.x + dx/m_div, pos.y + dy/m_div, pos.z));
	}
}
