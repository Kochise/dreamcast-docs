/*
   Tiki

   genmenu.cpp

   Copyright (C)2003,2004 Dan Potter
   Copyright (C)2005 Cryptic Allusion, LLC
*/

/* 
  This module implements a generic menu system. There are some pieces here
  that were more integrated into Feet of Fury which have been commented out
  for the moment until they can be more properly sorted out.

  The basic idea is that you derive a C++ class from this and implement the
  functionality that differs from the norm. If you have a very simple menu,
  then for example you can simply override the constructor (to add elements
  to the scene object) and the inputEvent method to receive keypresses
  from the user. If you wanted to do a custom exit sequence, you can also
  override startExit(). There is a lot more to override of course. Take a look
  through the module and the headers for some more ideas.

  GenericMenu is also, unfortunately, a bit DC specific right now but
  we're hoping to rectify this over time.

  This module was donated from Feet of Fury by Cryptic Allusion, LLC.

 */

#include "pch.h"

#include "Tiki/genmenu.h"
#include "Tiki/thread.h"
#include "Tiki/tikitime.h"
#include "Tiki/hid.h"
#include "Tiki/oggvorbis.h"
#include "Tiki/sound.h"
#include "Tiki/gl.h"

using namespace Tiki::GL;
using namespace Tiki::Audio;

GenericMenu::GenericMenu() {
	m_usebgm = false;
	m_cachebgm = false;
	
	m_bg[0] = m_bg[1] = m_bg[2] = 0.0f;

	m_exiting = false;
	m_exitCount = m_exitSpeed = 0.0f;

	m_totime = 0;
	m_timeout = 45;

	m_scene = new Layer();

	m_postDelay = 0;
	
	m_startTime = m_lastTime = Time::gettime();
	
	m_ec = new Hid::EventCollector(false);
}

GenericMenu::~GenericMenu() {
}

void GenericMenu::doMenu() {
	// Start background music if necessary
	if (m_usebgm) {
		m_bgm = new VorbisStream();
		if (m_bgm->load(m_bgmFn, true))
			m_bgm->start();
	}

	// Reset our timeout
	resetTimeout();

	// And start collecting events.
	m_ec->start();

	// Enter the main loop
	m_exiting = false;
	while (!m_exiting) {
		controlPerFrame();
		visualPerFrame();
	}

	// Stop collecting events now.
	m_ec->stop();

	// Ok, we're exiting -- do the same as before, but we'll exit out
	// entirely when the scene is finished (and music faded).
	while (!m_scene->isFinished() && m_exitCount > 0.0f) {
		m_exitCount -= m_exitSpeed;
		if (m_exitCount < 0.0f)
			m_exitCount = 0.0f;
		if (m_usebgm) {
			m_bgm->setVolume(m_exitCount);
		}
		visualPerFrame();
	}

	// Did we get a quit-now request?
	if (m_exitSpeed) {
		// We should be faded out now -- do three more frames to finish
		// clearing out the PVR buffered scenes.
		m_exitCount = 0;
		visualPerFrame();
		visualPerFrame();
		visualPerFrame();

		// Stop music if necessary
		if (m_usebgm) {
			m_bgm->stop();
		}

		if (m_postDelay)
			Time::sleep(m_postDelay * 1000);

		// Stop any sound effects
		Sound::stopAll();
	}
}

void GenericMenu::setPostDelay(int d) {
	m_postDelay = d;
}

void GenericMenu::visualPerFrame() {
	uint64 frameTime;
	
	m_scene->subRemoveFinished();
	m_scene->createSceneList();

	Frame::begin();

	if (m_exiting) {
#if TIKI_PLAT != TIKI_NDS
		glClearColor(m_bg[0]*m_exitCount, m_bg[1]*m_exitCount, m_bg[2]*m_exitCount, 1.0f);
#else
		glClearColor((uint8)((m_bg[0]*m_exitCount)*255),
                             (uint8)((m_bg[1]*m_exitCount)*255),
                             (uint8)((m_bg[2]*m_exitCount)*255));
#endif
	}
	else {
#if TIKI_PLAT != TIKI_NDS
		glClearColor(m_bg[0], m_bg[1], m_bg[2], 1.0f);
#else
		glClearColor((uint8)(m_bg[0]*255),
                             (uint8)(m_bg[1]*255),
                             (uint8)(m_bg[2]*255));
#endif
	}

	visualOpaqueList();

	Frame::transEnable();
	visualTransList();

	Frame::finish();
	
	m_scene->destroySceneList();

	frameTime=Time::gettime();
	m_scene->nextFrame(frameTime-m_lastTime);
	m_lastTime=frameTime;
}

void GenericMenu::visualOpaqueList() {
	m_scene->drawScene(Drawable::Opaque);
}

void GenericMenu::visualTransList() {
	m_scene->drawScene(Drawable::Trans);
}

void GenericMenu::controlPerFrame() {
	// Check for timeouts and send a message if we have one. In case the
	// subclass isn't paying attention, reset the counter as well.
	uint64 tm = Time::gettime() / 1000000;
	if ((tm - m_totime) > m_timeout) {
		resetTimeout();
		inputEvent(Event(Event::EvtTimeout));
	}
	
	// Check for regular HID events.
	Hid::Event evt;
	while (m_ec->getEvent(evt)) {
		processHidEvent(evt);
	}
}

// The default inputEvent just gives you simple debugging output so
// you know it works.
void GenericMenu::inputEvent(const Event & evt) {
}

void GenericMenu::startExit() {
	m_exiting = true;
	m_exitCount = 1.0f;
	// XXX
	m_exitSpeed = 1.0f/60.0f;
	// m_exitSpeed = 1.0f/hz;	// hz is 50 or 60
}

void GenericMenu::quitNow() {
	m_exiting = true;
	m_exitCount = 0.0f;
	m_exitSpeed = 0.0f;
}

void GenericMenu::setBgm(const string & fn, bool cache) {
	if (fn.length()) {
		m_bgmFn = fn;
		m_usebgm = true;
	} else
		m_usebgm = false;
	m_cachebgm = cache;
}

void GenericMenu::resetTimeout() {
	m_totime = (uint32)(Time::gettime() / 1000000);
}

void GenericMenu::setTimeout(uint32 v) {
	m_timeout = v;
}

void GenericMenu::setBg(float r, float g, float b) {
	m_bg[0] = r;
	m_bg[1] = g;
	m_bg[2] = b;
}

void GenericMenu::processHidEvent(const Hid::Event & evt) {
	// Just pass the event down as-is first.
	// And why exactly C++ can't deal with making a default copy constructor
	// from a base class is anyone's guess.
	Event newevt;
	newevt.type = evt.type;
	newevt.dev = evt.dev;
	newevt.tm = evt.tm;
	newevt.key = evt.key;
	newevt.btn = evt.btn;
	newevt.axis = evt.axis;
	newevt.axisValue = evt.axisValue;
	newevt.userCode = evt.userCode;
	newevt.x = evt.x;
	newevt.y = evt.y;
	newevt.port = evt.port;
	if (evt.dev && evt.dev->getType() == Hid::Device::TypeMouse) {
		Vector v = m_scene->getTranslate();
		newevt.x -= (int)v.x;
		newevt.y -= (int)v.y;
	}
	inputEvent(newevt);
	// process mouse events for possible object interaction
	if (evt.dev && evt.dev->getType() == Hid::Device::TypeMouse &&
	   (evt.type == Event::EvtBtnPress || evt.type == Event::EvtBtnRelease)) {
	}
	else if (evt.type == Event::EvtQuit) {
	// If we're receiving a HID Quit event, then translate that into KeyReset
	// as well (to deal with legacy code).
		newevt.type = Event::EvtKeypress;
		newevt.key = Event::KeyReset;
		inputEvent(newevt);
	} else if (evt.type == Event::EvtKeypress) {
		// Also translate these two. Eventually we may want some sort
		// of programmable mapping for joysticks and such.
		switch(evt.key) {
		case '\r':	// ENTER key
			newevt.key = Event::KeySelect;
			inputEvent(newevt);
			break;
		case Event::KeyEsc:
			newevt.key = Event::KeyCancel;
			inputEvent(newevt);
			break;
		default:
			break;
		}
	}
}

