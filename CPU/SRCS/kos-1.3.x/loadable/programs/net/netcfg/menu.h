/*      
   Network Configurator
        
   menu.h

   Copyright (C)2003 Cryptic Allusion, LLC
   Donated from Feet of Fury Peripheral Tester

   $Id: menu.h,v 1.1 2003/07/15 07:55:05 bardtx Exp $
*/

#ifndef __MENU_H
#define __MENU_H

#define MENU_OPTS 7

///////////////////////////////////////////////////////////////////////////////

#include <tsu/genmenu.h>

class SelBar;
class TextDisplay;
class SubMenu;
class Label;
class Font;
class Sound;

class Menu : public GenericMenu, public RefCnt {
public:
	Menu(Font * f);
	virtual ~Menu();

	virtual void startExit();
	virtual void inputEvent(const Event & evt);
	virtual void controlPerFrame();

	void moveSelection();
	void freeTextures();
	void reloadTextures();
	void exit();

	RefPtr<Scene>		m_level1;
	RefPtr<SelBar>		m_selbar;
	RefPtr<TextDisplay>	m_td;

	RefPtr<SubMenu>		m_menus[MENU_OPTS];
	RefPtr<SubMenu>		m_curmenu;		// Only if _active_
	int			m_sel;

	RefPtr<Font>		m_font;

	RefPtr<Sound>		m_cursor, m_select, m_cancel;

	List<Label>		m_labels;

	int			m_exitcode;
};

#endif	/* __MENU_H */

