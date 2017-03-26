/*      
   Network Configurator
        
   subexit.h

   Copyright (C)2003 Dan Potter
*/

#ifndef __SUBEXIT_H
#define __SUBEXIT_H

#include "submenu.h"

class SubExit : public SubMenu {
public:
	SubExit(Menu * m);
	virtual ~SubExit();

	virtual const char * getLabel();
	virtual int getDescrCnt();
	virtual const char ** getDescr();

	virtual bool select();
};

#endif	// __SUBEXIT_H
