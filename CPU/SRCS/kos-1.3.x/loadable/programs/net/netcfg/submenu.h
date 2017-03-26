/*      
   Network Configurator
        
   submenu.h

   Copyright (C)2003 Cryptic Allusion, LLC
   Donated from Feet of Fury Peripheral Tester
*/

#ifndef __SUBMENU_H
#define __SUBMENU_H

#include <tsu/genmenu.h>

class Menu;

class SubMenu : public GenericMenu, public RefCnt {
public:
	SubMenu(Menu * m) {
		m_parent = m;
		reset();
	}
	virtual ~SubMenu() { }

	virtual void inputEvent(const Event & evt) {
		if (evt.type == Event::EvtKeypress)
			processKey(evt.key);
	}

	virtual void processKey(Event::KeyConstant key) {
		if (key == Event::KeyCancel)
			setFinished();
	}

	virtual const char * getLabel() { return "Unnamed"; }
	
	virtual int getDescrCnt() { return 2; }
	
	virtual const char ** getDescr() {
		static const char * descr[] = {
			"A nifty description goes here.",
			"Maybe when this is written."
		};
		return descr;
	}

	virtual float getDescrSize() { return 20.0f; }

	virtual bool select() { return false; }

	virtual bool periodic() { return false; }

	Scene * getScene() { return m_scene; }

	virtual void reset() {
		m_finished = false;
		m_scene->subRemoveAll();
	}

	void setFinished() { m_finished = true; }
	bool isFinished() const { return m_finished; }


	float			m_lbly;

	Menu			* m_parent;
	bool			m_finished;
};

#endif	/* __SUBMENU_H */

