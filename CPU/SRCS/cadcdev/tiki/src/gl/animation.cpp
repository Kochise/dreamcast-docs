/*
   Tiki

   animation.cpp

   Copyright (C)2002,2003,2004 Dan Potter
   Copyright (C)2005 Cryptic Allusion, LLC
*/

#include "pch.h"
#include "Tiki/animation.h"
#include "Tiki/drawable.h"

using namespace Tiki::GL;

TIKI_OBJECT_NAME(Animation)
TIKI_OBJECT_BEGIN(Object, Animation)
TIKI_OBJECT_END(Animation)

Animation::Animation() {
	m_lastUpdate = 0;
}

Animation::~Animation() {
}

void Animation::triggerAdd(Trigger *t) {
	m_triggers.insertHead(t);
}

void Animation::triggerRemove(Trigger *tr) {
	m_triggers.del(tr);
}

void Animation::triggerRemoveAll() {
	m_triggers.delAll();
}

void Animation::nextFrame(Drawable *t, uint64 tm) {
	m_lastUpdate = tm;
}

void Animation::trigger(Drawable *d) {
	// Call each active trigger
	ListNode<Trigger> *t, *tn;

	t = m_triggers.getHead();
	while (t) {
		tn = t->getNext();
		(*t)->trigger(d, this);
		t = tn;
	}
}

void Animation::complete(Drawable *d) {
	// Call any completion triggers
	trigger(d);

	// Remove us from the parent Drawable
	d->animRemove(this);
}
