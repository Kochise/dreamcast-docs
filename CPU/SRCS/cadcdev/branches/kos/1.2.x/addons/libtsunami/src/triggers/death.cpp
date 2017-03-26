/* 
   Tsunami for KallistiOS ##version##
   
   death.cpp
   
   (c)2002 Dan Potter
*/

#include <tsu/triggers/death.h>
#include <tsu/drawable.h>

CVSID("$Id: death.cpp,v 1.1 2002/09/09 08:43:38 bardtx Exp $");

Death::Death() {
}

Death::~Death() {
}

void Death::trigger(Drawable *t, Animation *a) {
	// Mark our parent drawable as "finished"
	t->setFinished();

	// Go the way of the dodo ourselves
	Trigger::trigger(t, a);
}

