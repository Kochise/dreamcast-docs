/* KallistiOS ##version##

   arch/gba/include/spinlock.h
   (c)2001 Dan Potter
   
   $Id: spinlock.h,v 1.2 2002/11/06 08:34:54 bardtx Exp $
*/

#ifndef __ARCH_SPINLOCK_H
#define __ARCH_SPINLOCK_H

/* Defines processor specific spinlocks; if you include this file, you
   must first include kos/thread.h. */

/* Spinlock data type */
/* typedef int spinlock_t; */
typedef char spinlock_t;

/* Value initializer */
#define SPINLOCK_INITIALIZER 0

/* Initialize a spinlock */
#define spinlock_init(A) *(A) = SPINLOCK_INITIALIZER

/* Spin on a lock */
/* #define spinlock_lock(A) do { \
		if (*(A)) { \
			while (*(A)) \
				; \
			*(A) = 1; \
		} \
	} while (0) */
#define spinlock_lock(A) do { } while (0)

/* Free a lock */
/* #define spinlock_unlock(A) do { \
		*(A) = 0; \
	} while (0) */
#define spinlock_unlock(A) do { } while (0)


#endif	/* __ARCH_SPINLOCK_H */

