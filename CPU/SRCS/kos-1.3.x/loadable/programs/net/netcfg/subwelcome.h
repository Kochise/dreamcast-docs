/*      
   Network Configurator
        
   subwelcome.h

   Copyright (C)2003 Dan Potter

   $Id: subwelcome.h,v 1.1 2003/07/15 07:55:06 bardtx Exp $
*/

#ifndef __SUBWELCOME_H
#define __SUBWELCOME_H

#include "submenu.h"

class SubWelcome : public SubMenu {
public:
	SubWelcome(Menu * m);
	virtual ~SubWelcome();

	virtual const char * getLabel();
	virtual int getDescrCnt();
	virtual const char ** getDescr();
};

#endif	// __SUBWELCOME_H
