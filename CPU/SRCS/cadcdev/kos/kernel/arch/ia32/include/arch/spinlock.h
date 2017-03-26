/* KallistiOS ##version##

   arch/dreamcast/include/spinlock.h
   (c)2001 Dan Potter
   
   $Id: spinlock.h,v 1.2 2003/08/02 09:14:46 bardtx Exp $
*/

#ifndef __ARCH_SPINLOCK_H
#define __ARCH_SPINLOCK_H

/* Defines processor specific spinlocks */

#include <sys/cdefs.h>
__BEGIN_DECLS

/* DC implementation uses threads most of the time */
#include <kos/thread.h>
#include <arch/irq.h>

/* Spinlock data type */
typedef volatile int spinlock_t;

/* Value initializer */
#define SPINLOCK_INITIALIZER 0

/* Initialize a spinlock */
#define spinlock_init(A) *(A) = SPINLOCK_INITIALIZER

/* Note here that even if threads aren't enabled, we'll still set the
   lock so that it can be used for anti-IRQ protection (e.g., malloc) */

/* Spin on a lock */
#define spinlock_lock(A) do { \
	int __x = irq_disable(); \
	while (*A) { \
		irq_restore(__x); \
		thd_pass(); \
		irq_disable(); \
	} \
	*A = 1; \
	irq_restore(__x); \
} while(0)

/* Free a lock */
#define spinlock_unlock(A) do { \
		*(A) = 0; \
	} while (0)

__END_DECLS

/* Determine if a lock is locked */
#define spinlock_is_locked(A) ( *(A) != 0 )

#endif	/* __ARCH_SPINLOCK_H */

