/*      
   Network Configurator
        
   subnetdrv.h

   Copyright (C)2003 Dan Potter
*/

#ifndef __SUBNETDRV_H
#define __SUBNETDRV_H

#include "submenu.h"

class Popup;

class SubNetDriver : public SubMenu {
public:
	SubNetDriver(Menu * m);
	virtual ~SubNetDriver();

	virtual const char * getLabel();
	virtual int getDescrCnt();
	virtual const char ** getDescr();

	virtual void inputEvent(const Event & evt);
	virtual bool select();

	RefPtr<Popup>	m_popup;
};

#endif	// __SUBNETDRV_H
