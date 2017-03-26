/*      
   Network Configurator

   starfield.h

   Copyright (C)2002 Cryptic Allusion, LLC
   Donated from Feet of Fury

   $Id: starfield.h,v 1.1 2003/07/15 07:55:06 bardtx Exp $
*/

#ifndef __STARFIELD_H
#define __STARFIELD_H

#include <tsu/drawable.h>

class StarField : public Drawable {
public:
	StarField(int ns);
	virtual ~StarField();

	virtual void draw(int list);

private:
	void polyPnt(float x, float y, float z, float size, uint32 color);

	int		m_ns;
	Vector		* m_stars;
};

#endif	/* __STARFIELD_H */

