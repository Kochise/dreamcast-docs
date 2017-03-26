/*
   Tsunami for KallistiOS ##version##

   alphafader.cpp

   (c)2002 Dan Potter
*/

#include <tsu/drawable.h>
#include <tsu/anims/alphafader.h>

CVSID("$Id: alphafader.cpp,v 1.2 2003/04/24 02:57:20 bardtx Exp $");

AlphaFader::AlphaFader(float fade_to, float delta) {
	m_fade_to = fade_to;
	m_delta = delta;
}

AlphaFader::~AlphaFader() { }

void AlphaFader::nextFrame(Drawable *t) {
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
