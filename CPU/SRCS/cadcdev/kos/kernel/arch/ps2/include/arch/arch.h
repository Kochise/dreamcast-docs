/* KallistiOS ##version##

   arch/ps2/include/arch.h
   (c)2001-2002 Dan Potter
   
   $Id: arch.h,v 1.2 2002/10/27 23:39:23 bardtx Exp $
*/

#ifndef __ARCH_ARCH_H
#define __ARCH_ARCH_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

/* This stuff is all wrong... probably needs to be updated for PS2 */
#if 0
/* Page size info (for MMU) */
#define PAGESIZE	4096
#define PAGESIZE_BITS	12
#define PAGEMASK	(PAGESIZE - 1)

/* Page count variable; in this case it's static, so we can
   optimize this quite a bit. */
#define page_count ((16*1024*1024 - 0x10000) / PAGESIZE)

/* Base address of available physical pages */
#define page_phys_base 0x8c010000
#endif	/* 0 */

/* Number of timer ticks per second */
#define HZ		100

/* Default thread stack size */
#define THD_STACK_SIZE	65536

/* More DC specific stuff, though we'll probably want equivalents
   eventually, so I'm leaving it here as a reminder. */
#if 0
/* Default video mode */
#define DEFAULT_VID_MODE	DM_640x480
#define DEFAULT_PIXEL_MODE	PM_RGB565

/* Default serial parameters */
#define DEFAULT_SERIAL_BAUD	57600
#define DEFAULT_SERIAL_FIFO	1
#endif	/* 0 */

/* Panic function */
void panic(const char *str) __noreturn;

/* Kernel C-level entry point */
void arch_main();

/* Potential exit paths from the kernel on arch_exit() */
#define ARCH_EXIT_RETURN	1

/* Set the exit path (default is RETURN) */
void arch_set_exit_path(int path);

/* Generic kernel "exit" point */
void arch_exit() __noreturn;

/* Kernel "return" point */
void arch_return() __noreturn;

/* Kernel "abort" point */
void arch_abort() __noreturn;

/* Call to run all ctors / dtors */
void arch_ctors();
void arch_dtors();

/* Hook to ensure linking of crtend.c */
void __crtend_pullin();

/* Use this macro to determine the level of initialization you'd like in
   your program by default. The defaults line will be fine for most things. */
#define KOS_INIT_FLAGS(flags)	uint32 __kos_init_flags = (flags)

extern uint32 __kos_init_flags;

/* Defaults */
#define INIT_DEFAULT \
	(INIT_IRQ | INIT_THD_PREEMPT)

/* Define a romdisk for your program, if you'd like one */
#define KOS_INIT_ROMDISK(rd)	void * __kos_romdisk = (rd)

extern void * __kos_romdisk;

/* State that you don't want a romdisk */
#define KOS_INIT_ROMDISK_NONE	NULL

/* Constants for the above */
#define INIT_NONE		0		/* Kernel enables */
#define INIT_IRQ		1
#define INIT_THD_PREEMPT	2
#define INIT_NET		4
#define INIT_MALLOCSTATS	8
#define INIT_OCRAM		16

/* PS2-specific arch init things */
void arch_real_exit() __noreturn;
int hardware_init();
void hardware_shutdown();
void syscall_init();

/* PS2-specific sleep mode function */
#define arch_sleep() do { \
	/* XXX WRITE ME */ \
	} while(0)

/* PS2-specific function to get the return address from the current function */
#define arch_get_ret_addr() ({ \
		ptr_t pr; \
		__asm__ __volatile__("sd	$31,%0\n" \
			: "=&z" (pr) \
			: /* no inputs */ \
			: "memory" ); \
	pr; })

#if 0	/* Not ported yet */

/* Please note that all of the following frame pointer macros are ONLY
   valid if you have compiled your code WITHOUT -fomit-frame-pointer. These
   are mainly useful for getting a stack trace from an error. */

/* DC specific function to get the frame pointer from the current function */
#define arch_get_fptr() ({ \
		uint32 fp; \
		__asm__ __volatile__("mov	r14,%0\n" \
			: "=&z" (fp) \
			: /* no inputs */ \
			: "memory" ); \
	fp; })

/* Pass in a frame pointer value to get the return address for the given frame */
#define arch_fptr_ret_addr(fptr) (*((uint32*)fptr))

/* Pass in a frame pointer value to get the previous frame pointer for the given frame */
#define arch_fptr_next(fptr) (*((uint32*)(fptr+4)))

#endif

__END_DECLS

#endif	/* __ARCH_ARCH_H */

