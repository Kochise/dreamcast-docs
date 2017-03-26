/*
   Network Configurator

   widget.cpp

   Copyright (C)2003 Cryptic Allusion, LLC
   Donated from Feet of Fury

   $Id: widget.cpp,v 1.1 2003/07/15 07:55:06 bardtx Exp $
*/

#include "widget.h"

Widget::Widget() {
	m_focused = false;
}

Widget::~Widget() {
}

void Widget::inputEvent(const GenericMenu::Event & evt) {
}

void Widget::setFocus(bool foc) {
	m_focused = foc;
}
