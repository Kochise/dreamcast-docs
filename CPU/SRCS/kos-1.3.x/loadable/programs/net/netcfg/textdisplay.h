/*      
   Network Configurator
        
   textdisplay.h

   Copyright (C)2002 Cryptic Allusion, LLC
   Donated from Feet of Fury

   $Id: textdisplay.h,v 1.1 2003/07/15 07:55:06 bardtx Exp $
*/

#ifndef __TEXTDISPLAY_H
#define __TEXTDISPLAY_H

#include <tsu/drawable.h>

class Font;

class TextDisplay : public Drawable {
public:
	TextDisplay(Font * fh, float ps, bool center = false);
	virtual ~TextDisplay();

	void setText(const char **text, int linecnt);
	void setBGAlpha(float a);
	void setFont(Font * f);
	void setSize(float s);

	// Get our pixel size (for sub-widgeting)
	void getSize(float & w, float & h);

	virtual void draw(int list);
	virtual void nextFrame();

private:
	float		m_w, m_h;
	float		m_ps;
	float		m_bga;
	int		m_line_cnt;
	RefPtr<Font>	m_fh;
	const char 	** m_text;
	int		m_text_len;
	bool		m_center;
};

#endif	/* __TEXTDISPLAY_H */

