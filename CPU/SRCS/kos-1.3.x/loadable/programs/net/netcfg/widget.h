/*      
   Network Configurator
        
   widget.h

   Copyright (C)2003 Cryptic Allusion, LLC
   Donated from Feet of Fury

   $Id: widget.h,v 1.1 2003/07/15 07:55:06 bardtx Exp $
*/

#ifndef __WIDGET_H
#define __WIDGET_H

/* A Widget is a particular kind of object (generally a Drawable) that can
   also accept input and potentially focus. */

#include <tsu/genmenu.h>

class Widget {
public:
	// Constructor / destructor
	Widget();
	virtual ~Widget();

	// Called to accept events to be processed. The enums from GenericMenu
	// are used here.
	virtual void inputEvent(const GenericMenu::Event & evt);

	// Get/Set our focused state.
	virtual void setFocus(bool foc);
	bool getFocused() const { return m_focused; }
	
protected:
	bool	m_focused;	// Are we focused?
};

#endif	/* __WIDGET_H */

