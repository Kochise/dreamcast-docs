/*
   Tsunami for KallistiOS ##version##
        
   banner.h

   (c)2002 Dan Potter

   $Id: banner.h,v 1.3 2003/04/24 02:57:20 bardtx Exp $
*/

#ifndef __TSUNAMI_DRW_BANNER_H
#define __TSUNAMI_DRW_BANNER_H

#include <plx/list.h>
#include <plx/sprite.h>
#include "../drawable.h"
#include "../texture.h"
#include "../color.h"

/** Banner -- a texture banner drawable. This drawable takes a texture (and
    optional UV coordinates) and draws a banner. */
class Banner : public Drawable {
public:
	Banner(int list, Texture * texture);
	virtual ~Banner();

	void setTexture(Texture * txr);

	// Points are:   2  4
	//               1  3
	void setUV(float u1, float v1, float u2, float v2, float u3, float v3, float u4, float v4);

	void setSize(float w, float h);

	virtual void draw(int list);

private:
	int			m_list;
	RefPtr<Texture>		m_texture;

	float	m_u1, m_v1, m_u2, m_v2;
	float	m_u3, m_v3, m_u4, m_v4;
	float	m_w, m_h;
};

#endif	/* __TSUNAMI_DRW_BANNER_H */

