/*
   Tiki

   timeline.h

   Copyright (C)2005 Cryptic Allusion, LLC
*/

#ifndef __TIKI_TIMELINE_H
#define __TIKI_TIMELINE_H

#include "list.h"
#include "object.h"
#include "timepoint.h"

namespace Tiki {

/*

Timelines drive all animation work in Tiki V2. They generally will be tied to a
real timer (like a system timer or other periodic timer) but they can also be tied
to any arbitrary time source which may move forward or backward (e.g. a scrubber
bar). However in this implementation, only monotonically increasing time sources
are considered. One other interesting type of Timeline is a localized one which
has its zero point at a non-zero point of a parent Timeline.

*/

class Timeline : public Object {
public:
	TIKI_OBJECT_DECLS(Timeline)

	/// Constructor / Destructor
	Timeline();
	virtual ~Timeline();

	/// Add a timepoint to our list of timepoints
	void timepointAdd(Timepoint *t);

	/// Remove a timepoint from our list of timepoints
	void timepointRemove(Timepoint *t);

	/// Remove all timepoints from our list of timepoints
	void timepointRemoveAll();
	
	/// Re-sort a timepoint into the proper place in the timeline. This
	/// should only be called for timepoints that are already in the timeline.
	void timepointReSort(Timepoint * t);
	
	/// Return the named timepoint, if we have it
	Timepoint * timepointGet(string name);

	/// This should be called periodically to move our internal
	/// counters and potentially trigger events. The value 'tm'
	/// should be monotonically increasing.
	void periodic(uint64 tm);

	/// Retrieves the time this last invocation of periodic() was called (absolute).
	uint64 curTimeAbs() const { return m_curTimeAbsolute; }
	
	/// Retrieves the time this last invocation of periodic() was called (relative).
	uint64 curTime() const { return curTimeAbs() + m_parentOffset; }

	/// Retrieves the time the previous invocation of periodic() was called (absolute).
	uint64 lastTimeAbs() const { return m_lastTimeAbsolute; }

	/// Retrieves the time the previous invocation of periodic() was called (relative).
	uint64 lastTime() const { return lastTimeAbs() + m_parentOffset; }

	/// Retrieves the number of microseconds since periodic() was previously called.
	uint64 timeElapsed() const { return m_curTimeAbsolute - m_lastTimeAbsolute; }

	/// Reset us so that the current time is our zero point. i.e. after
	/// this call, curTime() will return zero again.
	void reset();
	void setParentOffset(int64 tm);
	int64 getParentOffset() const { return m_parentOffset; }

private:
	List<Timepoint>	m_timepoints;		// Timepoints
	uint64		m_lastTimeAbsolute;	// The time before that
	uint64		m_curTimeAbsolute;	// Last time periodic() was called
	
	// Timelines can be cascaded. If we are a sub-timeline, then our time
	// value will be the value of the parent plus m_parentOffset.
	Timeline	* m_parent;		// Our parent Timeline (if any)
	int64		m_parentOffset;		// The offset from our parent (if any)
};

}

#endif	// __TIKI_TIMELINE_H

