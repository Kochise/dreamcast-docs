/* KallistiOS ##version##

   arch/dreamcast/include/arch/atexit.h
   (c)2002 Florian Schulze
   
   $Id: atexit.h,v 1.1 2002/02/15 20:20:46 bardtx Exp $
*/

#ifndef __ARCH_ATEXIT_H
#define __ARCH_ATEXIT_H

#include <sys/cdefs.h>
__BEGIN_DECLS

struct arch_atexit_handler {
	struct arch_atexit_handler *next;
	void (*handler)(void);
};

extern struct arch_atexit_handler *arch_atexit_handlers;

/* Call all the atexit() handlers */
void arch_atexit();

__END_DECLS

#endif	/* __ARCH_ATEXIT_H */

