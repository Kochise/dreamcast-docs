/*
 Tiki
 
 cursor.h
 
 Copyright (C)2005 Sam Steele
 */

#ifndef __TIKI_DRW_CURSOR_H
#define __TIKI_DRW_CURSOR_H

#include "Tiki/drawable.h"
#include "Tiki/hid.h"

namespace Tiki {
namespace GL {

/* TikiCursor is a Drawable that follows the mouse.  You can pass in (or subAdd) any drawables
	 as a pointer, or you can use the default pointerArrow. */
class TikiCursor : public Drawable {
public:
	TikiCursor(Drawable *cursor=NULL);
	~TikiCursor();
	
	void setCursor(Drawable *cursor);

protected:
	// HID input callback.
	static void hidCallback(const Hid::Event & evt, void * data);
	virtual void processHidEvent(const Hid::Event & evt);
	
private:
	int m_hidCookie;
};

};
};
#endif //__TIKI_DRW_CURSOR_H
