/*      
   Network Configurator
        
   subip.h

   Copyright (C)2003 Dan Potter
*/

#ifndef __SUBIP_H
#define __SUBIP_H

#include "submenu.h"

class IPEditor;

class SubIP : public SubMenu {
public:
	SubIP(Menu * m, const char * label, uint32 * value);
	virtual ~SubIP();

	virtual const char * getLabel();
	virtual int getDescrCnt();
	virtual const char ** getDescr();

	virtual void inputEvent(const Event & evt);
	virtual bool select();

	RefPtr<IPEditor>	m_popup;
	const char		* m_label;
	uint32			* m_value;
};

#endif	// __SUBIP_H
