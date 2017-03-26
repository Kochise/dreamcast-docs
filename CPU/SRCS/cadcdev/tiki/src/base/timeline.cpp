/*
   Tiki

   timeline.cpp

   Copyright (C)2005 Cryptic Allusion, LLC
*/

#include "pch.h"
#include "Tiki/timeline.h"

using namespace Tiki;

TIKI_OBJECT_NAME(Timeline)
TIKI_OBJECT_BEGIN(Object, Timeline)
TIKI_OBJECT_END(Timeline)

Timeline::Timeline() {
	m_curTimeAbsolute = m_lastTimeAbsolute = 0;
	m_parentOffset = 0;
}

Timeline::~Timeline() {
}

void Timeline::timepointAdd(Timepoint * t) {
	m_timepoints.insertSorted(t);
	assert( !t->getParent() );
	t->setParent(this);
}

void Timeline::timepointRemove(Timepoint * t) {
	assert( t->getParent() == this );
	t->setParent(NULL);
	m_timepoints.del(t);
}

void Timeline::timepointRemoveAll() {
	m_timepoints.delAll();
}

void Timeline::timepointReSort(Timepoint * ti) {
	// This could probably be a lot more efficient...
	ListNode<Timepoint> * t;
	t = m_timepoints.getHead();
	while (t) {
		if (t->getData() == ti) {
			t->reSort();
			return;
		}
		t = t->getNext();
	}

	// Called on an item not in our list.
	assert( false );
}

Timepoint * Timeline::timepointGet(string name) {
	// This could probably be a lot more efficient...
	ListNode<Timepoint> * t;
	t = m_timepoints.getHead();
	while (t) {
		if ((*t)->getObjectName() == name)
			return t->getData();
		t = t->getNext();
	}
	
	return NULL;
}

void Timeline::periodic(uint64 tm) {
	// Do housekeeping.
	m_lastTimeAbsolute = m_curTimeAbsolute;
	m_curTimeAbsolute = tm;
	
	uint64 currentTime = curTime();
	
	// Are we past the front timepoint(s) yet? If not, we've got
	// nothing to do (they're sorted), and if so we need to execute
	// and ditch them.
	ListNode<Timepoint> * t, * n;
	t = m_timepoints.getHead();
	while (t) {
		n = t->getNext();
		if ((*t)->getOffset() > currentTime)
			break;
		if (!(*t)->trigger(this))
			t->remove();
		t = n;
	}
}

void Timeline::reset() {
	m_parentOffset = -((int64)m_curTimeAbsolute);
}

void Timeline::setParentOffset(int64 tm) {
	m_parentOffset = tm;
}


















