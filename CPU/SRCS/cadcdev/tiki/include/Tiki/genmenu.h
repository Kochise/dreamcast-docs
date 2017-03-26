/*
   Tiki

   genmenu.h

   Copyright (C)2003 Dan Potter
   Copyright (C)2005 Cryptic Allusion, LLC
*/

#ifndef __TIKI_GENMENU_H
#define __TIKI_GENMENU_H

#include "Tiki/refcnt.h"
#include "Tiki/drawables/layer.h"
#include "Tiki/hid.h"
#include "Tiki/eventcollector.h"
#include "Tiki/oggvorbis.h"

/*

This defines a fully generic menu system. Basically what you do is
derive from this class and then implement the constructor (which adds
things to the internal scene object) and the inputEvent method (which
is triggered any time a key change is detected). Pretty much everything
else is taken care of by this base class, including background music
if you want it (set in constructor).

Note that during the operation of the menu we'll register for the HID
event input.

*/

namespace Tiki {
namespace GL {

class GenericMenu {
public:
	// Constructor / destructor
	GenericMenu();
	virtual ~GenericMenu();

	// Called to actually "do" the menu -- this method will only return
	// when the menu has been completed and removed from the screen or
	// whatnot. The object can then be queried for any result data.
	virtual void doMenu();

	// Event class. Contains data about an input event that occured.
	struct Event : public Hid::Event {
		// The user didn't do anything for too long.
		static const int EvtTimeout = EvtUser;
		
		// These are "pseudo-keys" which we interpret based on
		// key mappings and such.
		static const int KeySelect = KeySentinel + 1;
		static const int KeyCancel = KeySentinel + 2;
		static const int KeyReset = KeySentinel + 3;
		
		Event() : Hid::Event() { }
		Event(Type t) : Hid::Event(t) { }
		Event(int t) : Hid::Event((Type)t) { }
	};

	// Set a post-doMenu delay in case sounds may still be playing
	void setPostDelay(int ms);
	
protected:
	// HID input callback.
	virtual void processHidEvent(const Hid::Event & evt);

	// Called once per frame to update the screen. Generally no need
	// to override this method.
	virtual void visualPerFrame();
	virtual void visualOpaqueList();
	virtual void visualTransList();

	// Called once per frame to handle any control input events. Generally
	// no need to override this method.
	virtual void controlPerFrame();

	// Called any time an "input event" is detected. You should override
	// this to handle debounced key-style inputs and peripheral add/remove.
	virtual void inputEvent(const Event & evt);

	// Override this method to provide your own "start shutdown" code. This
	// method should also be called by you on an appropriate inputEvent.
	// If you override this method, make sure you call this parent impl.
	virtual void startExit();

	// Call this method to force the menu to quit instantly. This is helpful
	// if you want to transition to another menu, etc.
	virtual void quitNow();

	// Call this method to setup a background song to be played during the
	// menu. You should do this before calling doMenu(). The song will
	// be started with the menu and faded out on exit.
	virtual void setBgm(const string & fn, bool cache = false);

	// This method should be called any time the user does something that
	// would cancel the menu's timeout.
	virtual void resetTimeout();
	virtual void setTimeout(uint32 v);

	// Set background colors
	virtual void setBg(float r, float g, float b);

	// Name of the song we'll use for background music (if any). If this
	// is an empty string, we'll not use a song.
	string		m_bgmFn;
	bool		m_usebgm, m_cachebgm;

	// Background plane color
	float		m_bg[3];

	// Are we exiting? If so, we'll be fading music and backplane...
	bool		m_exiting;
	float		m_exitCount;
	float		m_exitSpeed;

	// When was the last time the user did something?
	uint32		m_totime;

	// How many seconds should we allow before triggering a timeout?
	uint32		m_timeout;

	// Our "scene" object
	RefPtr<Layer>	m_scene;

	// Post-doMenu delay in case sounds are still playing
	int		m_postDelay;
	
	// Our background stream, if we have on.
	RefPtr<Audio::VorbisStream>	m_bgm;
	
	// The time at which we started
	uint64 m_startTime;
	
	// The time of the last frame rendered
	uint64 m_lastTime;
	
	// Event collector object, so we can process incoming events
	// in the drawing thread.
	RefPtr<Hid::EventCollector>	m_ec;
};

}
}

#endif	/* __GENMENU_H */

