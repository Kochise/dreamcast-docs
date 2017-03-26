/*      
   Tsunami for KallistiOS ##version##
        
   birth.h

   Copyright (C)2003 Dan Potter

   $Id: death.h,v 1.1 2002/09/09 08:43:37 bardtx Exp $
*/

#ifndef __TSUNAMI_TRIG_BIRTH_H
#define __TSUNAMI_TRIG_BIRTH_H

#include "../trigger.h"

class Birth : public Trigger {
public:
	// Constructor / Destructor
	Birth(Drawable * newDrawable, Drawable * target = NULL);
	virtual ~Birth();

	virtual void trigger(Drawable *t, Animation *a);

private:
	RefPtr<Drawable>	m_newDrawable;
	RefPtr<Drawable>	m_target;
};

#endif	/* __TSUNAMI_TRIG_BIRTH_H */

