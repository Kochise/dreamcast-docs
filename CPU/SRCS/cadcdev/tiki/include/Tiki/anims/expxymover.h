/*
   Tiki

   expxymover.h

   Copyright (C)2002 Dan Potter
   Copyright (C)2005 Cryptic Allusion, LLC
*/

#ifndef __TIKI_ANIMS_EXPXYMOVER_H
#define __TIKI_ANIMS_EXPXYMOVER_H

#include "Tiki/animation.h"

namespace Tiki {
namespace GL {

/// Exponential object mover in the X/Y plane
class ExpXYMover : public Animation {
public:
	ExpXYMover(float dx, float dy, float maxx, float maxy);
	virtual ~ExpXYMover();

	virtual void nextFrame(Drawable *t, uint64 tm);

private:
	float	m_dx, m_dy, m_maxx, m_maxy;
};

};
};

#endif	// __TIKI_ANIMS_EXPXYMOVER_H
