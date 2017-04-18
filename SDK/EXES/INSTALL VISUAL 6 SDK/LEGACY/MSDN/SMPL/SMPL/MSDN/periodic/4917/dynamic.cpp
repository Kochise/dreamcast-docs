//----------------------------------------------------------------------
// 			(C) 1996, Allen I. Holub. All rights reserved.
//======================================================================
#include "dynamic.h"

namespace dynamic
{
	/*static*/ factory_list_ele *factory_list_ele::head = 0;
	//------------------------------------------------------------------
	void *create( const char *cls_name )
	{
		// Create a new object dynamically. Search the list of dynamic
		// objects and call the create_obj() until one of them succeedes
		// in making the required object. If you get to the end of the
		// list, you can't make the requested object.

		void					*new_object = 0;
		const factory_list_ele	*cur		= factory_list_ele::head;

		for( ; cur ; cur = cur->next )
			if( new_object = cur->manufacturer->create_obj(cls_name) )
				break;

		return new_object;
	}
	//------------------------------------------------------------------
	/*virtual*/ factory_list_ele::~factory_list_ele( void )
	{
		// When the factory<t> is destroyed, it's "manufacturer"
		// field is also destroyed, so this destructor is called.
		// Remove the current factory from the factory_list. The
		// list is not doubly linked, so we have to track over from
		// the left to find the node to delete. I've reduced code
		// size a bit by using double indirection. The nextp pointer
		// always holds the address of the pointer to the current node.
		// This will be either the address of the head-of-list pointer
		// or the address of the "next" field of the previous node,
		// depending on whether we're at the head of list or not. In
		// any event, the first item in the list is not a special case
		// and we won't have to keep pointers to both the current and
		// previous nodes to do the delete.

		factory_list_ele	**nextp = &factory_list_ele::head;

		for( ; *nextp ; nextp = &(*nextp)->next )
			if( *nextp == this )
			{
				*nextp = (*nextp)->next;
				break;
			}
	}
}
