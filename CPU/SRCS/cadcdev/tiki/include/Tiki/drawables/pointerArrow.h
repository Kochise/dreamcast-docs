/*
 Tiki
 
 pointerArrow.h
 
 Copyright (C)2005 Sam Steele
 */

#ifndef __TIKI_DRW_POINTER_ARROW_H
#define __TIKI_DRW_POINTER_ARROW_H

#include "Tiki/drawable.h"
#include "Tiki/color.h"

namespace Tiki {
namespace GL {

/* PointerArrow is an arrow-shaped Drawable, normally used as a Cursor pointer */
class PointerArrow : public Drawable {
public:
	PointerArrow();
	~PointerArrow();
	
	//Overloaded functions
	void draw(ObjType list);
};

};
};
#endif //__TIKI_DRW_POINTER_ARROW_H
