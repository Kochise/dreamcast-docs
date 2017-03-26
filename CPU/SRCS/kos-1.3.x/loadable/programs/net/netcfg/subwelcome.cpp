/*      
   Network Configurator
        
   subwelcome.cpp

   Copyright (C)2003 Dan Potter

   $Id: subwelcome.cpp,v 1.1 2003/07/15 07:55:06 bardtx Exp $
*/

#include "subwelcome.h"

SubWelcome::SubWelcome(Menu * m) : SubMenu(m) {
}

SubWelcome::~SubWelcome() { }

const char * SubWelcome::getLabel()  {
	return "Welcome";
}

int SubWelcome::getDescrCnt()  {
	return 10;
}

const char ** SubWelcome::getDescr()  {
	static const char * descr[] = {
		"Welcome to the KOS network",
		"configuration app. This util",
		"will allow you to create and",
		"edit a network configuration",
		"file on a VMU for use with",
		"any KOS network apps. Use the",
		"up and down keys on any",
		"attached controller or keyboard",
		"to move to a sub-menu and",
		"select it with A or Enter."
	};
	
	return descr;
}

