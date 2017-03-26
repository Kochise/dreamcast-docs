/*
   Tiki

   object.cpp

   Copyright (C)2005 Cryptic Allusion, LLC
*/

#include "pch.h"
#include "Tiki/object.h"

using namespace Tiki;

RefCnt::RefCnt() {
	m_refcnt = 0;
}

RefCnt::~RefCnt() {
	if (m_refcnt != 0) {
		Debug::printf("RefCnt::~RefCnt: **WARNING** My (%p), refcount isn't zero! It's %d.\n",
			this, m_refcnt);
	}
	assert( m_refcnt == 0 );
}

void RefCnt::ref() {
	assert( this != NULL );

	// This actually ought to be in plat, probably...
#if TIKI_PLAT == TIKI_WIN32
	InterlockedIncrement(&m_refcnt);
#else
	m_refcnt++;
#endif
}

void RefCnt::unref() {
	assert( this != NULL );

#if TIKI_PLAT == TIKI_WIN32
	InterlockedDecrement(&m_refcnt);
#else
	m_refcnt--;
#endif

	if (m_refcnt < 0) {
		Debug::printf("RefCnt::unref() refcount underflow! this=%p\n", this);
		assert( false );
	} else if (m_refcnt == 0) {
		delete this;
	}
}



Object::Object() {
	m_setup = false;
}

Object::~Object() {
}

void Object::setupIfNotSetup() {
	if (!m_setup) {
		setupName(NULL);
		setupEvents();
		m_setup = true;
	}
}

const string & Object::getClassName() {
	setupIfNotSetup();
	return m_className;
}

const string & Object::getObjectName() {
	return m_objName;
}

Object::OutletMap & Object::getOutletMap() {
	setupIfNotSetup();
	return m_outlets;
}

Object::ReceiverMap & Object::getReceiverMap() {
	setupIfNotSetup();
	return m_receivers;
}

// These are only and always called during setup, so there's no need to do
// setupIfNotSetup() (actually it'd recurse infinitely)
void Object::addReceiver(Selector sel, Receiver rcv) {
	m_receivers.insert(std::pair<Selector,Receiver>(sel, rcv));
}

void Object::addOutlet(Selector sel) {
	m_outlets.insert(std::pair<Selector,OutletTarget>(sel, OutletTarget(NULL, "")));
}

int Object::perform(Selector msg, Object * sender, Object * arg) {
	setupIfNotSetup();

	// Find the target method.
	ReceiverMap::iterator i = m_receivers.find(msg);
	if (i == m_receivers.end()) {
		Debug::printf("WARNING: Selector %s performed on object %s ignored!\n",
			msg.c_str(), m_className.c_str());
		return -1;
	}
	
	Receiver rcv = i->second;
	return (this->*rcv)(sender, arg);
}

int Object::emit(Selector msg, Object * arg) {
	setupIfNotSetup();
	
	// Find the target outlet.
	OutletMap::iterator i = m_outlets.find(msg);
	if (i == m_outlets.end())
		return -1;
	
	OutletTarget & target = i->second;
	Object * targetObj = target.first;
	Selector targetSel = target.second;
	if (targetSel == "")
		targetSel = msg;
	return targetObj->perform(targetSel, this, arg);
}

bool Object::connect(Selector sel, Object * target, Selector targetsel) {
	setupIfNotSetup();
	
	// Find the target outlet.
	OutletMap::iterator i = m_outlets.find(sel);
	if (i == m_outlets.end())
		return false;
	
	i->second = OutletTarget(target, targetsel);
	return true;
}

Object * Object::getTarget(Selector sel) {
	setupIfNotSetup();
	
	// Find the target outlet.
	OutletMap::iterator i = m_outlets.find(sel);
	if (i == m_outlets.end())
		return NULL;
	
	return i->second.first;
}

Object::Selector Object::getTargetSelector(Selector sel) {
	setupIfNotSetup();
	
	// Find the target outlet.
	OutletMap::iterator i = m_outlets.find(sel);
	if (i == m_outlets.end())
		return NULL;
	
	return i->second.second;
}

void Object::setupName(const char * name) {
	if (name == NULL)
		m_className = "Object";
	else
		m_className = name;
}

void Object::setupEvents(bool final) {
	if (final)
		setupEventsStart();
	if (final)
		setupEventsFinish();
}

void Object::setupEventsStart() {
}

void Object::setupEventsFinish() {
}
























