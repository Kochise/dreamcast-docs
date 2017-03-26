/*
   Tiki

   eventcollector.h

   Copyright (C)2005 Cryptic Allusion, LLC
*/

#ifndef __TIKI_EVENTCOLLECTOR_H
#define __TIKI_EVENTCOLLECTOR_H

#include "Tiki/refcnt.h"
#include "Tiki/hid.h"
#include "Tiki/thread.h"
#include <queue>

namespace Tiki {
namespace Hid {

/*

This class defines a very simple queueing event collector for
the Tiki HID system. When you instantiate it, it'll add itself to
the event listeners and simply record all received events internally
for later playback. This is very useful if you don't want to go to
all the trouble of properly receiving events yourself.

*/

class EventCollector : public RefCnt {
public:
	EventCollector(bool startListening = true);
	virtual ~EventCollector();
	
	// Start listening for events.
	void start();
	
	// Stop listening for events.
	void stop();
	
	// Are there any events available?
	bool eventsAvailable() const;
	
	// Are we listening for events?
	bool listening() const {
		return (m_cookie >= 0);
	}
	
	// Retrieve an event if one is available. Returns true if
	// you got one.
	bool getEvent(Event & evtOut);

protected:
	// Our static HID callback function.
	static void hidCallbackStatic(const Event & evt, void * data);
	
	// Non-static callback.
	void hidCallback(const Event & evt);
	
	// Callback cookie.
	int	m_cookie;
	
	// List of pending events recorded by the callback.
	std::queue<Event>	m_events;
	
	// Mutex to protect us (most likely events come from another thread).
	RefPtr<Thread::Mutex>	m_mutex;
};

}
}

#endif	// __TIKI_EVENTCOLLECTOR_H

