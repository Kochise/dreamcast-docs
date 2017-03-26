/*
   Tsunami for KallistiOS ##version##
        
   label.h

   (c)2002 Dan Potter

   $Id: label.h,v 1.2 2003/03/09 01:24:57 bardtx Exp $
*/

#ifndef __TSUNAMI_DRW_LABEL_H
#define __TSUNAMI_DRW_LABEL_H

#include "../drawable.h"
#include "../font.h"

class Label : public Drawable {
public:
	Label(Font * fh, const char *text, int size, bool centered, bool smear);
	virtual ~Label();

	void setText(const char * text);
	void setFont(Font * f);

	virtual void draw(int list);

private:
	RefPtr<Font>	m_fh;
	const char	* m_text;
	int		m_size;
	bool		m_centered;
	bool		m_smear;
};

#endif	/* __TSUNAMI_DRW_LABEL_H */

