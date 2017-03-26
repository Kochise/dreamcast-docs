/*
   Tiki

   animation.h

   Copyright (C)2002,2003,2004 Dan Potter
   Copyright (C)2005 Cryptic Allusion, LLC
*/

#ifndef __TIKI_ANIMATION_H
#define __TIKI_ANIMATION_H

#include "list.h"
#include "trigger.h"
#include "object.h"

namespace Tiki {
namespace GL {

class Drawable;

class Animation : public Object {
public:
	TIKI_OBJECT_DECLS(Animation)

	/// Constructor / Destructor
	Animation();
	virtual ~Animation();

	/// Add a trigger to our list of triggers
	void triggerAdd(Trigger *t);

	/// Remove a trigger from our list of triggers
	void triggerRemove(Trigger *t);

	/// Remove all triggers from our list of triggers
	void triggerRemoveAll();

	/// Move to the next frame of animation
	virtual void nextFrame(Drawable *t, uint64 tm);

	/// Retrieves the last time nextFrame() was called.
	uint64 lastUpdate() const { return m_lastUpdate; }

	/// Retrieves the number of microseconds since nextFrame() was last called.
	uint64 timeElapsed(uint64 tm) const { return tm - m_lastUpdate; }

protected:	
	/// Trigger any triggers
	virtual void trigger(Drawable *d);

	/// Call when the animation has completed
	virtual void complete(Drawable *t);

private:
	List<Trigger>	m_triggers;		// Animation triggers
	uint64		m_lastUpdate;		// Last time we updated
};

}
}

#endif	// __TIKI_ANIMATION_H

