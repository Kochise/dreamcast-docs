/*
 Tiki
 
 cursor.cpp
 
 Copyright (C)2005 Sam Steele
 */

#include "pch.h"

#include "Tiki/hid.h"
#include "Tiki/drawables/pointerArrow.h"
#include "Tiki/drawables/cursor.h"

using namespace Tiki::GL;
using namespace Tiki::Hid;

TikiCursor::TikiCursor(Drawable *pointer) {
	// Register us for HID input callbacks.
	m_hidCookie = callbackReg(hidCallback, this);
	assert( m_hidCookie >= 0 );
	
	//Our translation isn't relative to the parent
	m_t_prelative = false;
	setCursor(pointer);
}

void TikiCursor::setCursor(Drawable *pointer) {
	subRemoveAll();
	
	if(pointer==NULL) {
		subAdd(new PointerArrow());
	} else {
		subAdd(pointer);
	}
}

TikiCursor::~TikiCursor() {
	Hid::callbackUnreg(m_hidCookie);
}

void TikiCursor::hidCallback(const Event & evt, void * data) {
	assert( data );
	((TikiCursor *)data)->processHidEvent(evt);
}

void TikiCursor::processHidEvent(const Event & evt) {
	if(evt.dev == NULL) {
		return;
	}

	if (evt.type==Event::EvtMouseMove ) {
		setTranslate(Vector(evt.x,evt.y,getTranslate().z));
	}
}

