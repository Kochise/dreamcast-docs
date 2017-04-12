/* KallistiOS 1.1.6

   arch/dreamcast/include/arch.h
   (c)2001 Dan Potter
   
   $Id: arch.h,v 1.6 2002/01/13 02:18:49 bardtx Exp $
*/

#ifndef __ARCH_ARCH_H
#define __ARCH_ARCH_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <dc/video.h>

/* Page size info (for MMU) */
#define PAGESIZE	4096
#define PAGESIZE_BITS	12
#define PAGEMASK	(PAGESIZE - 1)

/* Page count variable; in this case it's static, so we can
   optimize this quite a bit. */
#define page_count ((16*1024*1024 - 0x10000) / PAGESIZE)

/* Base address of available physical pages */
#define page_phys_base 0x8c010000

/* Number of timer ticks per second */
#define HZ		100

/* Default thread stack size */
#define THD_STACK_SIZE	8192

/* Default video mode */
#define DEFAULT_VID_MODE	DM_640x480
#define DEFAULT_PIXEL_MODE	PM_RGB565

/* Default serial parameters */
#define DEFAULT_SERIAL_BAUD	57600
#define DEFAULT_SERIAL_FIFO	1

/* Panic function */
void panic(const char *str) __noreturn;

/* Prototype for the portable kernel main() */
int kernel_main(const char *args);

/* Kernel C-level entry point */
int arch_main();

/* Kernel "quit" point */
void arch_exit() __noreturn;

/* Kernel "reboot" call */
void arch_reboot() __noreturn;

/* Call to run all ctors / dtors */
void arch_ctors();
void arch_dtors();

/* Hook to ensure linking of crtend.c */
void __crtend_pullin();

/* Initialize all hardware in one sweep */
int kos_init_all(uint32 enables, void *romdisk);

/* Constants for the above */
#define NONE_ENABLE	0		/* Kernel enables */
#define IRQ_ENABLE	1
#define THD_ENABLE	2
#define TA_ENABLE	0x10000		/* DC-specific enables */
#define BASIC_ENABLE	(IRQ_ENABLE | THD_ENABLE)
#define ALL_ENABLE	(IRQ_ENABLE | THD_ENABLE | TA_ENABLE)
#define ROMDISK_NONE	((void*)0)

/* De-initialize all hardware in one sweep */
void kos_shutdown_all();

/* Dreamcast-specific arch init things */
void arch_real_exit() __noreturn;
int hardware_init();
void hardware_shutdown();
void syscall_init();

__END_DECLS

#endif	/* __ARCH_ARCH_H */

