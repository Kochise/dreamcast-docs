/*      
   Network Configurator
        
   ipeditor.h

   Copyright (C)2003 Dan Potter

   $Id: ipeditor.h,v 1.1 2003/07/15 07:55:05 bardtx Exp $
*/

#ifndef __IPEDITOR_H
#define __IPEDITOR_H

#include <stdlib.h>
#include "widget.h"

class MenuBox;
class SelBar;
class Sound;
class Font;
class Label;

class IPEditor : public Drawable, public Widget {
public:
	IPEditor(const char * title, Font * fnt, Sound * cursor, Sound * select, Sound * abort);
	virtual ~IPEditor();

	virtual void inputEvent(const GenericMenu::Event & evt);

	void setValue(uint32 val);
	uint32 getValue();
	bool getOk();

private:
	void	startExit();

	int		m_selectedQuad;

	RefPtr<Font>	m_font;
	RefPtr<Sound>	m_cursor, m_select, m_abort;

	RefPtr<MenuBox>	m_box;
	RefPtr<SelBar>	m_selbar;

	float		m_qw;

	RefPtr<Label>	m_title, m_quad[4], m_dot[3];
	char		m_quadStrs[4][6];

	bool		m_ok;
};

#endif	/* __IPEDITOR_H */

