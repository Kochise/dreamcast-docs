/*      
   Tsunami for KallistiOS ##version##
        
   font.h

   (c)2002 Dan Potter

   $Id: font.h,v 1.3 2003/04/24 02:57:20 bardtx Exp $
*/

#ifndef __TSUNAMI_FONT_H
#define __TSUNAMI_FONT_H

#include <plx/font.h>
#include "refcnt.h"
#include "vector.h"

class Font : public RefCnt {
public:
	Font(const char *fn = NULL, int list = PVR_LIST_TR_POLY);
	virtual ~Font();

	bool loadFromFile(const char * fn);
	
	void setColor(float r, float g, float b);
	void setAlpha(float a);
	void setSize(float size);

	void draw(float x, float y, float z, const char *text);
	void drawCentered(float x, float y, float z, const char *text);
	void smearDraw(float x, float y, float z, const char *text);
	void smearDrawCentered(float x, float y, float z, const char *text);

	void drawCharBegin(float x, float y, float z);
	Vector drawCharGetPos();
	void drawCharSetPos(const Vector &v);
	float drawChar(int ch);
	void drawCharEnd();
	
	void getCharExtents(int c, float * l, float * u, float * r, float * d);
	void getTextSize(const char *text, float * w, float * h);
	void upperleftCoords(const char * text, float *x, float *y);
	void centerCoords(const char * text, float *x, float *y);

	operator plx_font_t * () const { return m_font; }
	operator plx_fcxt_t * () const { return m_cxt; }

private:
	plx_font_t	* m_font;
	plx_fcxt_t	* m_cxt;
	int		m_list;
	float		m_a, m_r, m_g, m_b;
	float		m_ps;
};

#endif	/* __FONTHELPER_H */

