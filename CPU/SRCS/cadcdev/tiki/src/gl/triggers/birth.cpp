/* 
   Tiki
   
   birth.cpp
   
   Copyright (C)2003 Dan Potter
   Copyright (C)2005 Cryptic Allusion, LLC
*/

#include "pch.h"
#include "Tiki/triggers/birth.h"
#include "Tiki/drawable.h"

using namespace Tiki::GL;

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

