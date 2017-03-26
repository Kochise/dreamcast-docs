/*      
   Network Configurator
        
   menubox.h

   Copyright (C)2003 Cryptic Allusion, LLC
   Donated from Feet of Fury

   $Id: menubox.h,v 1.1 2003/07/15 07:55:06 bardtx Exp $
*/

#ifndef __MENUBOX_H
#define __MENUBOX_H

#include <tsu/drawable.h>

class MenuBox : public Drawable {
public:
	MenuBox(bool border = true);
	virtual ~MenuBox();

	virtual void draw(int list);
	virtual void nextFrame();

private:
	int	m_frame;
	bool	m_border;
};

#endif	/* __MENUBOX_H */

