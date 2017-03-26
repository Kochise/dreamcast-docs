/*
   Tiki

   trigger.cpp

   Copyright (C)2002,2003,2004 Dan Potter
   Copyright (C)2005 Cryptic Allusion, LLC
*/

#include "pch.h"
#include "Tiki/trigger.h"
#include "Tiki/animation.h"

using namespace Tiki::GL;

TIKI_OBJECT_NAME(Trigger)
TIKI_OBJECT_BEGIN(Object, Trigger)
TIKI_OBJECT_END(Trigger)

Trigger::Trigger() {
}

Trigger::~Trigger() {
}

void Trigger::trigger(Drawable *t, Animation *a) {
	// Autoclean ourselves once we've triggered
	a->triggerRemove(this);
}

