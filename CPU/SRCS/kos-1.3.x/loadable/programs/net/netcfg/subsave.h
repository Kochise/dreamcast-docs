/*      
   Network Configurator
        
   subsave.h

   Copyright (C)2003 Dan Potter
*/

#ifndef __SUBSAVE_H
#define __SUBSAVE_H

#include "submenu.h"

class MessageBox;
class SubSave : public SubMenu {
public:
	SubSave(Menu * m);
	virtual ~SubSave();

	virtual const char * getLabel();
	virtual int getDescrCnt();
	virtual const char ** getDescr();

	virtual bool select();

	virtual void inputEvent(const Event & evt);

	RefPtr<MessageBox>	m_popup;
};

#endif	// __SUBSAVE_H
