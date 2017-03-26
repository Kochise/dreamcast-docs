/*
   Network Configurator
   
   menu.cpp

   Copyright (C)2003 Cryptic Allusion, LLC
   Donated from Feet of Fury Peripheral Tester

   $Id: menu.cpp,v 1.1 2003/07/15 07:55:05 bardtx Exp $
*/

#include <tsu/genmenu.h>
#include <tsu/sound.h>
#include <tsu/drawables/label.h>
#include "selbar.h"
#include "textdisplay.h"
#include "starfield.h"

#include "menu.h"
#include "submenu.h"
#include "subwelcome.h"
#include "subnetdrv.h"
#include "subip.h"
#include "subsave.h"
#include "subexit.h"

#include "netcfg.h"

Menu::Menu(Font * f) {
	// Get our basic scene graph setup
	m_level1 = new Scene();
	m_scene->subAdd(m_level1);

	m_font = f;

	m_cursor = new Sound("cursor.wav");
	m_select = new Sound("select.wav");
	m_cancel = new Sound("cancel.wav");

	Label * lbl = new Label(m_font, "KOS Net Config v1.0", 24, true, false);
	lbl->setTranslate(Vector(320.0f, 32.0f, 10.0f));
	m_level1->subAdd(lbl);
	m_labels.insertHead(lbl);

	m_td = new TextDisplay(m_font, 20, true);
	m_td->setBGAlpha(0.4f);
	m_td->setTranslate(Vector(400.0f, 240.0f, 10.0f));
	m_level1->subAdd(m_td);

	m_menus[0] = new SubWelcome(this);
	m_menus[1] = new SubNetDriver(this);
	m_menus[2] = new SubIP(this, "IP Address", &cfg.ip);
	m_menus[3] = new SubIP(this, "Gateway", &cfg.gateway);
	m_menus[4] = new SubIP(this, "Netmask", &cfg.netmask);
	m_menus[5] = new SubSave(this);
	m_menus[6] = new SubExit(this);

	float longest = 0.0f;
	float y = 80.0f;
	for (int i=0; i<MENU_OPTS; i++) {
		m_menus[i]->m_lbly = y;
		y += 28.0f;

		float w, h;
		m_font->setSize(24);
		m_font->getTextSize(m_menus[i]->getLabel(), &w, &h);
		if (w > longest)
			longest = w;
		
		lbl = new Label(m_font, m_menus[i]->getLabel(), 24, false, false);
		lbl->setTranslate(Vector(16.0f, m_menus[i]->m_lbly, 10.0f));
		m_level1->subAdd(lbl);
		m_labels.insertHead(lbl);
	}

	m_sel = 0;

	float selx = 16.0f + longest/2;
	float selw = longest+4;
	m_selbar = new SelBar(selw, 20, 4);
	m_selbar->setTranslate(Vector(selx, m_menus[m_sel]->m_lbly, 9.0f));
	m_level1->subAdd(m_selbar);
	moveSelection();

	StarField * sf = new StarField(512);
	sf->setTranslate(Vector(0,0,1));
	m_scene->subAdd(sf);

	setBg(0.06f, 0.02f, 0.3f);
}

Menu::~Menu() {
}

void Menu::startExit() {
	m_scene->subRemoveAll();
	GenericMenu::startExit();
}

void Menu::inputEvent(const Event & evt) {
	if (evt.type != Event::EvtKeypress)
		return;

	if (m_curmenu) {
		m_curmenu->inputEvent(evt);
		if (m_curmenu->isFinished()) {
			m_scene->subRemove(m_curmenu->getScene());
			m_scene->subAdd(m_level1);
			m_curmenu->reset();
			m_curmenu = NULL;

			moveSelection();
		}

		return;
	}

	switch (evt.key) {

	case Event::KeySelect:
		if (!m_menus[m_sel]->select())
			m_cursor->play();
		else {
			m_select->play();
			m_curmenu = m_menus[m_sel];
			m_scene->subRemove(m_level1);
			m_scene->subAdd(m_curmenu->getScene());
		}
		break;

	/* case Event::KeyCancel:
		m_cancel->play();
		startExit();
		break; */

	case Event::KeyUp:
		m_sel--;
		if (m_sel < 0)
			m_sel += MENU_OPTS;
		moveSelection();
		m_cursor->play();
		break;

	case Event::KeyDown:
		m_sel++;
		if (m_sel >= MENU_OPTS)
			m_sel -= MENU_OPTS;
		moveSelection();
		m_cursor->play();
		break;
	
	}
}

void Menu::controlPerFrame() {
	GenericMenu::controlPerFrame();

	for (int i=0; i<MENU_OPTS; i++) {
		if (m_menus[i]->periodic())
			moveSelection();
	}
}

void Menu::moveSelection() {
	Vector p = m_selbar->getTranslate();
	m_selbar->setTranslate(Vector(p.x, m_menus[m_sel]->m_lbly, p.z));

	m_td->setText(m_menus[m_sel]->getDescr(), m_menus[m_sel]->getDescrCnt());
	m_td->setSize(m_menus[m_sel]->getDescrSize());
}

void Menu::exit() {
	startExit();
}
