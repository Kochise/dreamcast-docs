/*      
   Network Configurator
        
   subsave.cpp

   Copyright (C)2003 Dan Potter

   $Id: subsave.cpp,v 1.1 2003/07/15 07:55:06 bardtx Exp $
*/

#include "subsave.h"
#include "menu.h"
#include "netcfg.h"
#include "messagebox.h"
#include <tsu/sound.h>

SubSave::SubSave(Menu * m) : SubMenu(m) {
}

SubSave::~SubSave() { }

const char * SubSave::getLabel()  {
	return "Save";
}

int SubSave::getDescrCnt()  {
	return 5;
}

const char ** SubSave::getDescr()  {
	static const char * descr1[] = {
		"Press A or Enter to save the",
		"current config to the first",
		"available VMU. Make sure that",
		"a VMU with one block free is",
		"plugged in somewhere."
	};

	return descr1;
}

bool SubSave::select() {
	// Try to save
	int rv = netcfg_save(&cfg);

	m_popup = new MessageBox(24, m_parent->m_font);
	m_popup->setTranslate(Vector(320,240,10));
	if (rv < 0) {
		static const char *msg[] = {
			"We were not able to save the",
			"config. Please make sure that at",
			"least one VMU with enough blocks",
			"is inserted and try again."
		};
		m_popup->setText(msg, 4);
		m_parent->m_cancel->play();
	} else {
		static const char *msg[] = {
			"The file was saved successfully."
		};
		m_popup->setText(msg, 1);
		m_parent->m_select->play();
	}
	m_scene->subAdd(m_popup);

	return true;
}

void SubSave::inputEvent(const Event & evt) {
	if (evt.type == Event::EvtKeypress) {
		m_popup = NULL;
		m_parent->m_select->play();
		setFinished();
	}
}
