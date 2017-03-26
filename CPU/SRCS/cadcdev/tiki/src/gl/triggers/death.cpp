/* 
   Tiki
   
   death.cpp
   
   Copyright (C)2003 Dan Potter
   Copyright (C)2005 Cryptic Allusion, LLC
*/

#include "pch.h"
#include "Tiki/triggers/death.h"
#include "Tiki/drawable.h"

using namespace Tiki::GL;

Death::Death(Drawable * target) {
	m_target = target;
}

Death::~Death() {
}

void Death::trigger(Drawable *t, Animation *a) {
	// Mark our parent drawable as "finished"
	if (m_target)
		m_target->setFinished();
	else
		t->setFinished();

	// Go the way of the dodo ourselves
	Trigger::trigger(t, a);
}

