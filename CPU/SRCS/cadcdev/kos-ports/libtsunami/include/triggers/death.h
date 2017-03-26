/*      
   Tsunami for KallistiOS ##version##
        
   death.h

   (c)2002 Dan Potter

   $Id: death.h,v 1.1 2002/09/09 08:43:37 bardtx Exp $
*/

#ifndef __TSUNAMI_TRIG_DEATH_H
#define __TSUNAMI_TRIG_DEATH_H

#include "../trigger.h"

class Death : public Trigger {
public:
	// Constructor / Destructor
	Death(Drawable * target = NULL);
	virtual ~Death();

	virtual void trigger(Drawable *t, Animation *a);
private:
	RefPtr<Drawable>	m_target;
};

#endif	/* __TSUNAMI_TRIG_DEATH_H */

