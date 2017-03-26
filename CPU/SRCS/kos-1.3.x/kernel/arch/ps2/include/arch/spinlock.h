/* KallistiOS ##version##

   arch/ps2/include/spinlock.h
   (c)2001-2002 Dan Potter
   
   $Id: spinlock.h,v 1.3 2002/11/06 08:41:03 bardtx Exp $
*/

#ifndef __ARCH_SPINLOCK_H
#define __ARCH_SPINLOCK_H

/* Defines processor specific spinlocks */

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <kos/thread.h>

/* Spinlock data type */
typedef volatile int spinlock_t;

/* Value initializer */
#define SPINLOCK_INITIALIZER 0

/* Initialize a spinlock */
#define spinlock_init(A) *(A) = SPINLOCK_INITIALIZER

/* Note here that even if threads aren't enabled, we'll still set the
   lock so that it can be used for anti-IRQ protection (e.g., malloc) */

/* Spin on a lock; we should probably get something a bit more elegant
   here, but what the heck... ll/sc are pretty ridiculously complicated
   and the manual doesn't say for sure if they prevent interrupts anyway. */
#define spinlock_lock(A) do { \
	spinlock_t * __lock = A; \
  try_again: \
	irq_disable(); \
	if (*__lock) { \
		irq_enable(); \
		thd_pass(); \
		goto try_again; \
	} else { \
		*__lock = 1; \
	} \
} while (0)

/* Free a lock */
#define spinlock_unlock(A) do { \
		*(A) = 0; \
	} while (0)

__END_DECLS

/* Determine if a lock is locked */
#define spinlock_is_locked(A) ( *(A) != 0 )

#endif	/* __ARCH_SPINLOCK_H */

