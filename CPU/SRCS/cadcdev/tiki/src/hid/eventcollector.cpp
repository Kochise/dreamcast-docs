/*
   Tiki

   eventcollector.cpp

   Copyright (C)2005 Cryptic Allusion, LLC
*/

#include "pch.h"
#include "Tiki/eventcollector.h"

using namespace Hid;

EventCollector::EventCollector(bool startListening) {
	m_cookie = -1;
	m_mutex = new Thread::Mutex();
	if (startListening)
		start();
}

EventCollector::~EventCollector() {
	if (m_cookie >= 0)
		stop();
}

void EventCollector::start() {
	Thread::AutoLock lock(m_mutex);

	assert( m_cookie < 0 );
	m_cookie = callbackReg(hidCallbackStatic, this);
}

void EventCollector::stop() {
	Thread::AutoLock lock(m_mutex);

	assert( m_cookie >= 0 );
	callbackUnreg(m_cookie);
	m_cookie = -1;
	
	m_events = std::queue<Event>();
}

bool EventCollector::eventsAvailable() const {
	Thread::AutoLock lock(m_mutex);
	return !m_events.empty();
}

bool EventCollector::getEvent(Event & evtOut) {
	Thread::AutoLock lock(m_mutex);
	if (m_events.empty())
		return false;
	
	evtOut = m_events.front(); m_events.pop();
	return true;
}

void EventCollector::hidCallbackStatic(const Event & evt, void * data) {
	assert( data );
	((EventCollector *)data)->hidCallback(evt);
}

void EventCollector::hidCallback(const Event & evt) {
	Thread::AutoLock lock(m_mutex);
	if (m_cookie >= 0)
		m_events.push(evt);
}




