/*      
   Tsunami for KallistiOS ##version##
        
   animation.h

   (c)2002 Dan Potter

   $Id: animation.h,v 1.2 2003/04/24 02:57:20 bardtx Exp $
*/

#ifndef __TSUNAMI_ANIMATION_H
#define __TSUNAMI_ANIMATION_H

class Drawable;

#include "list.h"
#include "trigger.h"

class Animation : public RefCnt {
public:
	/// Constructor / Destructor
	Animation();
	virtual ~Animation();

	/// Add a trigger to our list of triggers
	void triggerAdd(Trigger *t);

	/// Remove a trigger from our list of triggers
	void triggerRemove(Trigger *t);

	/// Remove all triggers from our list of triggers
	void triggerRemoveAll();

	// Move to the next frame of animation
	virtual void nextFrame(Drawable *t);

protected:	
	/// Trigger any triggers
	virtual void trigger(Drawable *d);

	/// Call when the animation has completed
	virtual void complete(Drawable *t);

private:
	List<Trigger>	m_triggers;		// Animation triggers
};

#endif	/* __TSUNAMI_ANIMATION_H */

