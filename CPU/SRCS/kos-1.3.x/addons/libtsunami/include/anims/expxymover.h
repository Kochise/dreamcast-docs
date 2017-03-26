/*
   Tsunami for KallistiOS ##version##

   expxymover.h

   (c)2002 Dan Potter

   $Id: expxymover.h,v 1.1 2002/09/09 08:43:37 bardtx Exp $
*/

#ifndef __TSUNAMI_ANIMS_EXPXYMOVER_H
#define __TSUNAMI_ANIMS_EXPXYMOVER_H

#include "../animation.h"

/// Exponential object mover in the X/Y plane
class ExpXYMover : public Animation {
public:
	ExpXYMover(float dx, float dy, float maxx, float maxy);
	virtual ~ExpXYMover();

	virtual void nextFrame(Drawable *t);

private:
	float	m_dx, m_dy, m_maxx, m_maxy;
};

#endif	/* __TSUNAMI_ANIMS_EXPXYMOVER_H */
