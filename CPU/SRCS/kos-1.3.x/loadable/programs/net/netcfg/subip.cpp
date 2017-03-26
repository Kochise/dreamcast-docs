/*      
   Network Configurator

   subip.cpp

   Copyright (C)2003 Dan Potter

   $Id: subip.cpp,v 1.1 2003/07/15 07:55:06 bardtx Exp $
*/

#include <tsu/sound.h>
#include <tsu/texture.h>
#include "subip.h"
#include "ipeditor.h"
#include "menu.h"

SubIP::SubIP(Menu * m, const char * label, uint32 * value) : SubMenu(m) {
	m_label = label;
	m_value = value;
}

SubIP::~SubIP() { }

const char * SubIP::getLabel()  {
	return m_label;
}

int SubIP::getDescrCnt()  {
	return 5;
}

const char ** SubIP::getDescr()  {
	static char buf[64] = "foo";
	static const char * descr[] = {
		NULL,
		"Press A or Enter to edit",
		"this setting.",
		"The current value is",
		buf
	};
	descr[0] = m_label;

	sprintf(buf, "%ld.%ld.%ld.%ld",
		(*m_value >> 24) & 0xff,
		(*m_value >> 16) & 0xff,
		(*m_value >> 8) & 0xff,
		(*m_value >> 0) & 0xff);
	
	return descr;
}

bool SubIP::select() {
	m_popup = new IPEditor(m_label, m_parent->m_font,
		m_parent->m_cursor, m_parent->m_select, m_parent->m_cancel);
	m_popup->setTranslate(Vector(320,240,1));
	m_popup->setValue(*m_value);
	m_scene->subAdd(m_popup);

	return true;
}

void SubIP::inputEvent(const Event & evt) {
	if (evt.type == Event::EvtKeypress) {
		m_popup->inputEvent(evt);
		if (m_popup->isFinished()) {
			if (m_popup->getOk())
				*m_value = m_popup->getValue();

			m_popup = NULL;
			setFinished();
		}
	}
}
