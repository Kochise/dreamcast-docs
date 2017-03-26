/*
   Tiki

   banner.h

   Copyright (C)2002 Dan Potter
   Copyright (C)2005 Cryptic Allusion, LLC
*/

#ifndef __TIKI_DRW_BANNER_H
#define __TIKI_DRW_BANNER_H

#include "Tiki/drawable.h"
#include "Tiki/texture.h"
#include "Tiki/color.h"

namespace Tiki {
namespace GL {

/** Banner -- a texture banner drawable. This drawable takes a texture (and
    optional UV coordinates) and draws a banner. */
class Banner : public Drawable {
public:
	Banner(ObjType t, Texture * texture);
	virtual ~Banner();

	void setTexture(Texture * txr);

	// Points are:   2  4
	//               1  3
	void setUV(float u1, float v1, float u2, float v2, float u3, float v3, float u4, float v4);

	void setSize(float w, float h);

	virtual void draw(ObjType t);

protected:
	RefPtr<Texture>		m_texture;
private:
	ObjType			m_list;

	float	m_u1, m_v1, m_u2, m_v2;
	float	m_u3, m_v3, m_u4, m_v4;
	float	m_w, m_h;
};

};
};

#endif	// __TIKI_DRW_BANNER_H

