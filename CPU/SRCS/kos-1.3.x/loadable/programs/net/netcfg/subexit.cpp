/*      
   Network Configurator
   
   subexit.cpp

   Copyright (C)2003 Dan Potter

   $Id: subexit.cpp,v 1.1 2003/07/15 07:55:06 bardtx Exp $
*/

#include "subexit.h"
#include "menu.h"

SubExit::SubExit(Menu * m) : SubMenu(m) {
}

SubExit::~SubExit() { }

const char * SubExit::getLabel()  {
	return "Exit";
}

int SubExit::getDescrCnt()  {
	return 1;
}

const char ** SubExit::getDescr()  {
	static const char * descr1[] = {
		"Press A or Enter to exit."
	};

	return descr1;
}

bool SubExit::select() {
	m_parent->exit();
	return false;
}
