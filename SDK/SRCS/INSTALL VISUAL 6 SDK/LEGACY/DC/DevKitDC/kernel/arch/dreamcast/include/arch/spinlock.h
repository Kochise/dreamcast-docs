/* KallistiOS 1.1.6

   arch/dreamcast/include/spinlock.h
   (c)2001 Dan Potter
   
   $Id: spinlock.h,v 1.4 2002/01/14 05:56:04 bardtx Exp $
*/

#ifndef __ARCH_SPINLOCK_H
#define __ARCH_SPINLOCK_H

/* Defines processor specific spinlocks */

#include <sys/cdefs.h>
__BEGIN_DECLS

/* DC implementation uses threads most of the time */
#include <kos/thread.h>

/* Spinlock data type */
typedef volatile int spinlock_t;

/* Value initializer */
#define SPINLOCK_INITIALIZER 0

/* Initialize a spinlock */
#define spinlock_init(A) *(A) = SPINLOCK_INITIALIZER

/* Spin on a lock */
#define spinlock_lock(A) do { \
    if (thd_enabled) { \
	spinlock_t * __lock = A; \
	int __gotlock = 0; \
	while(1) { \
	    asm volatile ("tas.b @%1\n\t" \
			  "movt %0\n\t" \
			  : "=r" (__gotlock) : "r" (__lock) : "t", "memory"); \
	    if (!__gotlock) \
		thd_pass(); \
	    else break; \
	} \
    } \
} while (0)

/* Free a lock */
#define spinlock_unlock(A) do { \
		if (thd_enabled) { \
			*(A) = 0; \
		} \
	} while (0)

__END_DECLS

#endif	/* __ARCH_SPINLOCK_H */

