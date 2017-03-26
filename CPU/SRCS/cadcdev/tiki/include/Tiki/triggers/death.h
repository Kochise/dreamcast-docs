/*      
   Tiki
        
   death.h

   Copyright (C)2002 Dan Potter
   Copyright (C)2005 Cryptic Allusion, LLC
*/

#ifndef __TIKI_TRIG_DEATH_H
#define __TIKI_TRIG_DEATH_H

#include "../trigger.h"

namespace Tiki {
namespace GL {

class Death : public Trigger {
public:
	// Constructor / Destructor
	Death(Drawable * target = NULL);
	virtual ~Death();

	virtual void trigger(Drawable *t, Animation *a);
private:
	RefPtr<Drawable>	m_target;
};

};
};

#endif	// __TIKI_TRIG_DEATH_H

