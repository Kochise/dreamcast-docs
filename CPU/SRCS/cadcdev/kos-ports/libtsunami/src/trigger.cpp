/* 
   Tsunami for KallistiOS ##version##
   
   trigger.cpp
   
   (c)2002 Dan Potter
*/

#include <tsu/trigger.h>
#include <tsu/animation.h>

CVSID("$Id: trigger.cpp,v 1.1 2002/09/09 08:43:37 bardtx Exp $");

Trigger::Trigger() {
}

Trigger::~Trigger() {
}

void Trigger::trigger(Drawable *t, Animation *a) {
	// Autoclean ourselves once we've triggered
	a->triggerRemove(this);
}

