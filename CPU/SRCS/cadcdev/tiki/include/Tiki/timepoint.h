/*      
   Tiki
        
   timepoint.h

   Copyright (C)2005 Cryptic Allusion, LLC
*/

#ifndef __TIKI_TIMEPOINT_H
#define __TIKI_TIMEPOINT_H

#include "object.h"

namespace Tiki {

/*

Timepoint objects can be attached to the Timeline at various points. When the
Timeline reaches the given point (or rather, since a Timeline is usually updated
in discrete intervals, once it gets past the given point), the Timepoint will be
triggered.

Every object dealing with a Timeline can attach new Timepoints to it and move
around existing ones. For example a periodic Timepoint might re-instantiate itself
(or move itself) on the Timeline at a later time. Some other object might cause
a future Timepoint to move forward or backward, delaying or speeding up its
occurrence.

*/

class Timeline;

class Timepoint : public Object {
public:
	TIKI_OBJECT_DECLS(Timepoint)
	TIKI_OBJECT_EMITS("timepointReached:")		// Parameter: Timeline

	// Constructor / Destructor
	Timepoint();
	Timepoint(uint64 offset);
	virtual ~Timepoint();

	// Get/Set the offset.
	uint64 getOffset() const;
	void setOffset(uint64 offset);
	
	// "Bump" methods: lets you quickly adjust this timepoint to
	// trigger again later.
	void bump(uint64 offset);

	// Create a new timepoint representative of "bumping" this one. This is helpful
	// if you need to spawn a new event.
	Timepoint * newFromBump(uint64 offset);

	// Called by Timeline to trigger us. Returns true if we still
	// need to be called again later.
	bool trigger(Timeline * tm);

	// This is needed for the sorted list.
	bool operator<(const Timepoint & other) const {
		return m_offset < other.m_offset;
	}

	Timeline * getParent() const { return m_parent; }
	void setParent(Timeline * p) {
		m_parent = p;
	}

protected:
	Timeline	* m_parent;	// The timeline we're attached to (if any)
	uint64		m_offset;
};

}

#endif	// __TIKI_TIMEPOINT_H

