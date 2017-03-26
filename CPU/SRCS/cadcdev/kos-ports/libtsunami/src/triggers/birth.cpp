/* 
   Tsunami for KallistiOS ##version##
   
   birth.cpp
   
   Copyright (C)2003 Dan Potter
*/

#include <tsu/triggers/birth.h>
#include <tsu/drawable.h>

CVSID("$Id: death.cpp,v 1.1 2002/09/09 08:43:38 bardtx Exp $");

Birth::Birth(Drawable * newDrawable, Drawable * target) {
	m_newDrawable = newDrawable;
	m_target = target;
}

Birth::~Birth() {
}

void Birth::trigger(Drawable *t, Animation *a) {
	// Insert the next object into the parent
	if (m_target)
		m_target->subAdd(m_newDrawable);
	else
		t->subAdd(m_newDrawable);

	// Remove ourselves
	Trigger::trigger(t, a);
}

