
/*
 *	StaticInitializers.c	-	static initializer/destructor support for RISC targets
 *
 *	Copyright © 1995-1999 Metrowerks, Inc. All Rights Reserved.
 *
 *
 *	THEORY OF OPERATION
 *
 *	For any file that contains static/global objects that require runtime initialization
 *	or construction, the compiler generates a static initializer function of the form:
 *
 *		void __sinit_<filename>(void) { ... }
 *
 *	The linker is responsible for gathering these together and generating an array
 *	of pointers to them:
 *
 *		typedef void (*StaticInitializer)(void);
 *		extern StaticInitializer __sinit__[];
 *
 *	When the compiler generates code to call initializers for global variables and
 *	nonlocal static variables, it calls the function __register_global_object() to
 *	register the constructed object for destruction.
 *
 *	When the program exits, it calls __destroy_global_chain() to call destructors
 *	for the registered objects, in the reverse order of their construction.
 *
 *	If the program has no static initializers, the linker-generated symbol __sinit__
 *	may have the value 0, so we need to check for that below.
 *
 */

#include <CPlusLib.h>
#include <NMWException.h>


	/*	private types	*/
	
typedef void (*StaticInitializer)(void);


	/*	external data	*/

extern StaticInitializer __sinit__[];


	/*	public data		*/

DestructorChain *__global_destructor_chain;


/*
 *	__call_static_initializers	-	call all static initializer functions
 *
 */

void __call_static_initializers(void)
{
	StaticInitializer s, *p;
	
		/*	see if the static initializer table exists	*/
	
	if (__sinit__ == 0)
		return;
		
		/*	call all static initializers in the table	*/
	
	for (p = __sinit__; (s = *p) != 0; p++)
		s();
}


/*
 *	__destroy_global_chain	-	destroy all constructed global objects
 *
 */

void __destroy_global_chain(void)
{
	DestructorChain	*gdc;

	while((gdc = __global_destructor_chain) != 0) {
		__global_destructor_chain = gdc->next;
		DTORCALL_COMPLETE(gdc->destructor, gdc->object);
	}
}
