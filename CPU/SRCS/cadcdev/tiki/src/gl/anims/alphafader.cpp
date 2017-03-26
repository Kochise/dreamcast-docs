/*
   Tiki

   alphafader.cpp

   Copyright (C)2002,2003,2004 Dan Potter
   Copyright (C)2005 Cryptic Allusion, LLC
*/

#include "pch.h"
#include "Tiki/drawable.h"
#include "Tiki/anims/alphafader.h"

using namespace Tiki::GL;

// XXX delta -> time
AlphaFader::AlphaFader(float fade_to, float delta) {
	m_fade_to = fade_to;
	m_delta = delta;
}

AlphaFader::~AlphaFader() { }

void AlphaFader::nextFrame(Drawable *t, uint64 tm) {
	Color c = t->getTint();
	c.a += m_delta;
	t->setTint(c);
	if (m_delta < 0.0f) {
		if (c.a <= m_fade_to) {
			c.a = m_fade_to;
			t->setTint(c);
			complete(t);
		}
	} else {
		if (c.a >= m_fade_to) {
			c.a = m_fade_to;
			t->setTint(c);
			complete(t);
		}
	}
}
