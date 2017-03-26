/*      
   Network Configurator
        
   subnetdrv.cpp

   Copyright (C)2003 Dan Potter

   $Id: subnetdrv.cpp,v 1.1 2003/07/15 07:55:06 bardtx Exp $
*/

#include <tsu/sound.h>
#include <tsu/texture.h>
#include "subnetdrv.h"
#include "popup.h"
#include "menu.h"
#include "netcfg.h"

SubNetDriver::SubNetDriver(Menu * m) : SubMenu(m) {
}

SubNetDriver::~SubNetDriver() { }

const char * SubNetDriver::getLabel()  {
	return "Net Driver";
}

int SubNetDriver::getDescrCnt()  {
	return 8;
}

const char ** SubNetDriver::getDescr()  {
	static const char * descr[] = {
		"- Net driver selection -",
		"KOS network apps currently",
		"work with the Broadband",
		"Adapter and the Lan Adapter.",
		"Press A or Enter to pick",
		"which device you have.",
		"Current selection is",
		NULL
	};

	if (!strcmp(cfg.driver, "bba"))
		descr[7] = "Broadband Adapter";
	else if (!strcmp(cfg.driver, "la"))
		descr[7] = "Lan Adapter";
	else if (cfg.driver[0] == 0)
		descr[7] = "<Not Set>";
	else
		descr[7] = cfg.driver;

	return descr;
}

bool SubNetDriver::select() {
	m_popup = new Popup("Select Type", true, m_parent->m_font,
		m_parent->m_cursor, m_parent->m_select, m_parent->m_cancel);
	m_popup->addOption("Broadband Adapter");
	m_popup->addOption("Lan Adapter");
	m_popup->setTranslate(Vector(320,240,1));
	m_scene->subAdd(m_popup);

	return true;
}

void SubNetDriver::inputEvent(const Event & evt) {
	if (evt.type == Event::EvtKeypress) {
		m_popup->inputEvent(evt);
		int res = m_popup->getResult();
		if (res == -2) {
			m_popup = NULL;
			m_parent->m_cancel->play();
			setFinished();
		} else if (res >= 0) {
			int sel = m_popup->getResult();

			if (sel == 0)
				strcpy(cfg.driver, "bba");
			else if (sel == 1)
				strcpy(cfg.driver, "la");

			setFinished();
		}
	}
}
