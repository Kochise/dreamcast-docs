/* 
   Network Configurator

   ipeditor.cpp

   Copyright (C)2003 Dan Potter

   $Id: ipeditor.cpp,v 1.1 2003/07/15 07:55:05 bardtx Exp $
*/

#include <math.h>
#include <dc/fmath.h>
#include <tsu/font.h>
#include <tsu/sound.h>
#include <tsu/genmenu.h>
#include <tsu/drawables/label.h>
#include "ipeditor.h"
#include "menubox.h"
#include "selbar.h"

IPEditor::IPEditor(const char * title, Font * fnt, Sound * cursor, Sound * select, Sound * abort) {
	m_selectedQuad = 0;

	m_font = fnt;

	m_cursor = cursor;
	m_select = select;
	m_abort = abort;

	float ow, oh, pw, ph;
	fnt->setSize(18);
	fnt->getTextSize("000", &ow, &oh);
	fnt->getTextSize(".", &pw, &ph);
	m_qw = ow;

	float tw = ow*4 + pw*3 + 8;

	m_box = new MenuBox();
	m_box->setScale(Vector(440, 24*5, 1));
	
	m_title = new Label(fnt, title, 18, true, false);
	m_title->setTranslate(Vector(0,-24*2,1));
	m_box->subAdd(m_title);

	RefPtr<Label> instr = new Label(fnt, "Use triggers or Pgup/Pgdn to move by 10", 18, true, false);
	instr->setTranslate(Vector(0,-24,1));
	m_box->subAdd(instr);

	strcpy(m_quadStrs[0], "0");
	strcpy(m_quadStrs[1], "0");
	strcpy(m_quadStrs[2], "0");
	strcpy(m_quadStrs[3], "0");

	float x = -tw/2 + 4;
	for (int i=0; i<4; i++) {
		m_quad[i] = new Label(fnt, m_quadStrs[i], 18, false, false);
		m_quad[i]->setTranslate(Vector(x, 24, 10));
		m_box->subAdd(m_quad[i]);

		x += ow;

		if (i < 3) {
			m_dot[i] = new Label(fnt, ".", 18, false, false);
			m_dot[i]->setTranslate(Vector(x, 24, 10));
			m_box->subAdd(m_dot[i]);
		}

		x += pw;
	}

	m_selbar = new SelBar(0.0f, 0.0f, 0.0f);
	m_selbar->setTint(Color(1.0f, 1.0f, 1.0f, 0.0f));
	m_selbar->setTranslate(m_quad[0]->getTranslate() + Vector(m_qw/2,0,-1));
	m_selbar->setSize(m_qw, 18,2);

	subAdd(m_box);
	subAdd(m_selbar);

	m_ok = false;
}

IPEditor::~IPEditor() {
}

void IPEditor::inputEvent(const GenericMenu::Event & evt) {
	if (evt.type != GenericMenu::Event::EvtKeypress)
		return;

	switch (evt.key) {

	case GenericMenu::Event::KeyLeft:
		m_selectedQuad--;
		if (m_selectedQuad < 0)
			m_selectedQuad += 4;
		m_selbar->setTranslate(m_quad[m_selectedQuad]->getTranslate() + Vector(m_qw/2,0,-1));
		m_cursor->play();
		break;

	case GenericMenu::Event::KeyRight:
		m_selectedQuad++;
		if (m_selectedQuad >= 4)
			m_selectedQuad -= 4;
		m_selbar->setTranslate(m_quad[m_selectedQuad]->getTranslate() + Vector(m_qw/2,0,-1));
		m_cursor->play();
		break;

	case GenericMenu::Event::KeyUp:
		{
			int val = atoi(m_quadStrs[m_selectedQuad]);
			val++;
			if (val > 255)
				val -= 256;
			sprintf(m_quadStrs[m_selectedQuad], "%d", val);
		}
		m_cursor->play();
		break;

	case GenericMenu::Event::KeyPgdn:
		{
			int val = atoi(m_quadStrs[m_selectedQuad]);
			val+=10;
			if (val > 255)
				val -= 256;
			sprintf(m_quadStrs[m_selectedQuad], "%d", val);
		}
		m_cursor->play();
		break;

	case GenericMenu::Event::KeyDown:
		{
			int val = atoi(m_quadStrs[m_selectedQuad]);
			val--;
			if (val < 0)
				val += 256;
			sprintf(m_quadStrs[m_selectedQuad], "%d", val);
		}
		m_cursor->play();
		break;

	case GenericMenu::Event::KeyPgup:
		{
			int val = atoi(m_quadStrs[m_selectedQuad]);
			val-=10;
			if (val < 0)
				val += 256;
			sprintf(m_quadStrs[m_selectedQuad], "%d", val);
		}
		m_cursor->play();
		break;

	case GenericMenu::Event::KeySelect:
		// m_result = m_selectedQuad;
		startExit();
		m_select->play();
		m_ok = true;
		break;

	case GenericMenu::Event::KeyCancel:
		startExit();
		m_abort->play();
		m_ok = false;
		break;
	
	}
}

void IPEditor::startExit() {
	setFinished();
}

void IPEditor::setValue(uint32 val) {
	sprintf(m_quadStrs[0], "%d", (val >> 24) & 0xff);
	sprintf(m_quadStrs[1], "%d", (val >> 16) & 0xff);
	sprintf(m_quadStrs[2], "%d", (val >> 8) & 0xff);
	sprintf(m_quadStrs[3], "%d", (val >> 0) & 0xff);
}

uint32 IPEditor::getValue() {
	uint32 val = 0;

	val |= atoi(m_quadStrs[0]) << 24;
	val |= atoi(m_quadStrs[1]) << 16;
	val |= atoi(m_quadStrs[2]) << 8;
	val |= atoi(m_quadStrs[3]) << 0;

	return val;
}

bool IPEditor::getOk() {
	return m_ok;
}
                        

