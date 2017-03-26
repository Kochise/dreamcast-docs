/*      
   Tiki
        
   tee.h

   Copyright (C)2005 Cryptic Allusion, LLC
*/

#ifndef __TIKI_TEE_H
#define __TIKI_TEE_H

#include "object.h"
#include "list.h"
#include <list>

namespace Tiki {

/*

Tee defines a placeholder object which receives all messages and passes them
on to a list of sub-objects.

(Not yet written)

*/

class Tee : public Object {
public:
	TIKI_OBJECT_DECLS(Tee)

	// Constructor / Destructor
	Tee();
	virtual ~Tee();

	// Add an item to the distributor.
	void add(Object * item);
	
	// Remove an item from the distributor.
	void remove(Object * item);

	// An iterator to access the contents of our list.
	typedef std::list<Object *> ObjectList;
	typedef ObjectList::iterator iterator;
	
	// Gets the head of our list.
	iterator begin();

	// Our implementation of perform accepts any selector and performs
	// it on all sub-objects.
	virtual int perform(Selector sel, Object * sender, Object * arg);

protected:
	ObjectList	m_list;
};

}

#endif	// __TIKI_TEE_H

