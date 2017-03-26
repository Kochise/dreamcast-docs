/*      
   Tsunami for KallistiOS ##version##
        
   oneshot.h

   Copyright (C)2003 Dan Potter

   $Id: death.h,v 1.1 2002/09/09 08:43:37 bardtx Exp $
*/

#ifndef __TSUNAMI_TRIG_ONESHOT_H
#define __TSUNAMI_TRIG_ONESHOT_H

/* This defines a one-shot trigger which makes a callback to a compatible
   object. You can pass an arbitrary value along as well to be passed back
   to the callback. Just implement the OneShot::Target interface. */

#include "../trigger.h"

class OneShot : public Trigger {
public:
	class Target {
	public:
		virtual void shoot(int code) = 0;
		virtual RefCnt * getRefCnt() = 0;
	};

	// Constructor / Destructor
	OneShot(Target * t, int code) {
		m_target = t;
		m_ref = t->getRefCnt();
		m_code = code;
	}
	virtual ~OneShot() { }

	virtual void trigger(Drawable *t, Animation *a) {
		m_target->shoot(m_code);
		Trigger::trigger(t, a);
	}

private:
	Target		* m_target;
	RefPtr<RefCnt>	m_ref;
	int		m_code;
};

#endif	/* __TSUNAMI_TRIG_BIRTH_H */

