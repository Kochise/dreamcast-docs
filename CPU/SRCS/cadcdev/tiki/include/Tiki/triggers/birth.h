/*      
   Tiki
        
   birth.h

   Copyright (C)2003 Dan Potter
   Copyright (C)2005 Cryptic Allusion, LLC
*/

#ifndef __TIKI_TRIG_BIRTH_H
#define __TIKI_TRIG_BIRTH_H

#include "../trigger.h"

namespace Tiki {
namespace GL {

class Birth : public Trigger {
public:
	// Constructor / Destructor
	Birth(Drawable * newDrawable, Drawable * target = NULL);
	virtual ~Birth();

	virtual void trigger(Drawable *t, Animation *a);

private:
	RefPtr<Drawable>	m_newDrawable;
	RefPtr<Drawable>	m_target;
};

};
};

#endif	// __TIKI_TRIG_BIRTH_H

