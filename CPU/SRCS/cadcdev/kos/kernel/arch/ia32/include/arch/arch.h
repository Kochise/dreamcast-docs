/* KallistiOS ##version##

   arch/ia32/include/arch.h
   Copyright (C)2001,2003 Dan Potter
   
   $Id: arch.h,v 1.2 2003/08/02 23:09:26 bardtx Exp $
*/

#ifndef __ARCH_ARCH_H
#define __ARCH_ARCH_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

/* Page size info (for MMU) */
#define PAGESIZE	4096
#define PAGESIZE_BITS	12
#define PAGEMASK	(PAGESIZE - 1)

/* Page count variable; in this case it's static, so we can
   optimize this quite a bit. */
// XXX Need to ask the BIOS at start time
#define page_count ((32*1024*1024 - 0x10000) / PAGESIZE)

/* Base address of available physical pages */
#define page_phys_base 0x00010000

/* Number of timer ticks per second */
#define HZ		100

/* Default thread stack size */
#define THD_STACK_SIZE	8192

/* Default serial parameters */
#define DEFAULT_SERIAL_BAUD	57600
#define DEFAULT_SERIAL_FIFO	1

/* Do we need symbol prefixes? */
#define ELF_SYM_PREFIX ""
#define ELF_SYM_PREFIX_LEN 0

/* Panic function */
void panic(const char *str) __noreturn;

/* Prototype for the portable kernel main() */
int kernel_main(const char *args);

/* Kernel C-level entry point */
int arch_main();

/* Generic kernel "exit" point */
void arch_exit() __noreturn;

/* Kernel "return" point */
void arch_return() __noreturn;

/* Kernel "abort" point */
void arch_abort() __noreturn;

/* Kernel "reboot" call */
void arch_reboot() __noreturn;

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
#define INIT_NONE		0x0000		/* Kernel enables */
#define INIT_IRQ		0x0001
#define INIT_THD_PREEMPT	0x0002
#define INIT_NET		0x0004
#define INIT_MALLOCSTATS	0x0008
#define INIT_QUIET		0x0010

/* Call this function to remove all arch-specific traces of a process */
struct kprocess;
void arch_remove_process(struct kprocess * proc);

/* ia32 specific sleep mode function */
#define arch_sleep() do { \
		__asm__ __volatile__("hlt"); \
	} while(0)

/* ia32 specific function to get the return address from the current function */
#define arch_get_ret_addr() (0)

/* Please note that all of the following frame pointer macros are ONLY
   valid if you have compiled your code WITHOUT -fomit-frame-pointer. These
   are mainly useful for getting a stack trace from an error. */

/* ia32 specific function to get the frame pointer from the current function */
#define arch_get_fptr() (0)

/* Pass in a frame pointer value to get the return address for the given frame */
#define arch_fptr_ret_addr(fptr) (*((uint32*)fptr))

/* Pass in a frame pointer value to get the previous frame pointer for the given frame */
#define arch_fptr_next(fptr) (*((uint32*)(fptr+4)))

/* Returns true if the passed address is likely to be valid. Doesn't
   have to be exact, just a sort of general idea. */
#define arch_valid_address(ptr) ((ptr_t)(ptr) >= 0x00010000 && (ptr_t)(ptr) < 0x01000000)

__END_DECLS

#endif	/* __ARCH_ARCH_H */

