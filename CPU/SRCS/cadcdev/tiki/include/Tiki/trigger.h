/*      
   Tiki
        
   trigger.h

   Copyright (C)2002 Dan Potter
   Copyright (C)2005 Cryptic Allusion, LLC
*/

#ifndef __TIKI_TRIGGER_H
#define __TIKI_TRIGGER_H

#include "list.h"
#include "object.h"

namespace Tiki {
namespace GL {

class Drawable;
class Animation;
class Trigger;

class Trigger : public Object {
public:
	TIKI_OBJECT_DECLS(Trigger)

	// Constructor / Destructor
	Trigger();
	virtual ~Trigger();

	// Called when we have reached the trigger point in the
	// given animation/drawable
	virtual void trigger(Drawable *t, Animation *a);
};

}
}

#endif	// __TIKI_TRIGGER_H

