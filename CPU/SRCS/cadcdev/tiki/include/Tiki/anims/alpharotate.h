/*
   Tiki

   alpharotate.h

   Copyright (C)2005 Atani Software
*/

#ifndef __TIKI_ANIMS_ALPHAROTATE_H
#define __TIKI_ANIMS_ALPHAROTATE_H

#include "Tiki/animation.h"

namespace Tiki {
namespace GL {

/// Fades the alpha value of an object
class AlphaRotate : public Animation {
	public:
		AlphaRotate(float delta = 1.0f/60.0f) : m_delta(delta) {};
		virtual void nextFrame(Drawable *t, uint64 tm)
		{
			Color c = t->getTint();
			if(c.a < 0.0f || c.a > 1.0f) m_delta *= -1;
			c.a += m_delta;
			t->setTint(c);			
		}
	private:
		float m_delta;
};

};
};

#endif	// __TIKI_ANIMS_ALPHAFADER_H
