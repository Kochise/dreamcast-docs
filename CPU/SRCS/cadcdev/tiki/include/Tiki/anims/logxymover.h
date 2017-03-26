/*
   Tiki

   logxymover.h

   Copyright (C)2002 Dan Potter
   Copyright (C)2005 Cryptic Allusion, LLC
*/

#ifndef __TIKI_ANIMS_LOGXYMOVER_H
#define __TIKI_ANIMS_LOGXYMOVER_H

#include "Tiki/animation.h"
#include "Tiki/drawable.h"

namespace Tiki {
namespace GL {

/// Logarithmic object mover in the X/Y plane
class LogXYMover : public Animation {
public:
	LogXYMover(float dstx, float dsty, float divisor = 8.0f);
	virtual ~LogXYMover();

	virtual void nextFrame(Drawable *t, uint64 tm);

private:
	float	m_dstx, m_dsty, m_div;
};

};
};

#endif	// __TIKI_ANIMS_LOGXYMOVER_H
