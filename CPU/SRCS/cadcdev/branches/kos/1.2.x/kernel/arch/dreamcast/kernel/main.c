/* KallistiOS ##version##

   main.c
   (c)2000 Dan Potter
*/

#include <stdio.h>
#include <malloc.h>
#include <arch/syscall.h>
#include <arch/dbgio.h>
#include <arch/timer.h>
#include <arch/arch.h>
#include <arch/atexit.h>
#include <arch/irq.h>
#include <arch/rtc.h>
#include <dc/ubc.h>
#include <dc/pvr.h>
#include <dc/vmufs.h>

#include "initall_hdrs.h"

CVSID("$Id: main.c,v 1.28 2003/04/24 03:04:24 bardtx Exp $");

extern int _bss_start, end;

/* This really ought to be prototyped in a header */
int	mm_init();

/* Ditto */
int	main(int argc, char **argv);

/* Double-ditto */
extern const char banner[];

/* Auto-init stuff: comment out here if you don't like this stuff
   to be running in your build, and also below in arch_main() */
/* #if 0 */
int arch_auto_init() {
	dbgio_printk_func old;

	if (!(__kos_init_flags & INIT_NO_DCLOAD))
		fs_dcload_init_console();	/* Init dc-load console, if applicable */
	dbgio_init();			/* Init debug IO and print a banner */
	if (__kos_init_flags & INIT_QUIET)
		dbgio_set_printk(dbgio_null_write);
	dbglog(DBG_INFO, "\n--\n");
	dbglog(DBG_INFO, banner);
	
	irq_init();			/* IRQs */
	irq_disable();			/* Turn on exceptions */
	timer_init();			/* Timers */
	hardware_sys_init();		/* DC low-level hardware init */
	syscall_init();			/* System call interface */

	/* Initialize our timer */
	timer_ms_enable();
	rtc_init();

	/* Threads */
	if (__kos_init_flags & INIT_THD_PREEMPT)
		thd_init(THD_MODE_PREEMPT);
	else
		thd_init(THD_MODE_COOP);

	fs_init();			/* VFS */
	fs_ramdisk_init();		/* Ramdisk */
	fs_romdisk_init();		/* Romdisk */

	hardware_periph_init();		/* DC peripheral init */

	if (__kos_romdisk != NULL) {
		fs_romdisk_mount("/rd", __kos_romdisk, 0);
	}
	if (!(__kos_init_flags & INIT_NO_DCLOAD) && *DCLOADMAGICADDR == DCLOADMAGICVALUE) {
		dbglog(DBG_INFO, "dc-load console support enabled\n");
		fs_dcload_init();
	}
	fs_iso9660_init();
	vmufs_init();
	fs_vmu_init();

	/* Now comes the optional stuff */
	if (__kos_init_flags & INIT_IRQ) {
		irq_enable();		/* Turn on IRQs */
		maple_wait_scan();	/* Wait for the maple scan to complete */
	}
	if (!(__kos_init_flags & INIT_NO_DCLOAD) && *DCLOADMAGICADDR == DCLOADMAGICVALUE &&
		(__kos_init_flags & INIT_NET))
	{
		old = dbgio_set_printk(dbgio_write_str);
	}
	if (__kos_init_flags & INIT_NET) {
		net_init();		/* Enable networking (and drivers) */
	}
	if (!(__kos_init_flags & INIT_NO_DCLOAD) && *DCLOADMAGICADDR == DCLOADMAGICVALUE &&
		(__kos_init_flags & INIT_NET))
	{
		// dbgio_set_printk(old);
		fs_dclnative_init();
		dbglog(DBG_INFO, "dc-load-ip native support enabled\n");
	}


	return 0;
}

void arch_auto_shutdown() {
	irq_disable();
	snd_shutdown();
	timer_shutdown();
	hardware_shutdown();
	net_shutdown();
	pvr_shutdown();
	fs_dcload_shutdown();
	fs_vmu_shutdown();
	vmufs_shutdown();
	fs_iso9660_shutdown();
	fs_ramdisk_shutdown();
	fs_romdisk_shutdown();
	fs_shutdown();
	thd_shutdown();
	rtc_shutdown();
}
/* endif */

/* This is the entry point inside the C program */
int arch_main() {
	uint8 *bss_start = (uint8 *)(&_bss_start);
	uint8 *bss_end = (uint8 *)(&end);
	int rv;

	/* Ensure that we pull in crtend.c in the linking process */
	__crtend_pullin();

	/* Ensure that UBC is not enabled from a previous session */
	ubc_disable_all();

	/* Clear out the BSS area */
	memset(bss_start, 0, bss_end - bss_start);

	/* Initialize memory management */
	mm_init();

	/* Do auto-init stuff */
	arch_auto_init();

	/* Run ctors */
	arch_ctors();

	/* Call the user's main function */
	rv = main(0, NULL);

	/* Call kernel exit */
	arch_exit();

	return rv;
}

/* Set the exit path (default is RETURN) */
int arch_exit_path = ARCH_EXIT_RETURN;
void arch_set_exit_path(int path) {
	assert(path >= ARCH_EXIT_RETURN && path <= ARCH_EXIT_REBOOT);
	arch_exit_path = path;
}

/* Does the actual shutdown stuff for a proper shutdown */
void arch_shutdown() {
	/* Run dtors */
	arch_atexit();
	arch_dtors();

	dbglog(DBG_CRITICAL, "arch: shutting down kernel\n");

	/* Turn off UBC breakpoints, if any */
	ubc_disable_all();
	
	/* Do auto-shutdown... or use the "light weight" version underneath */
#if 1
	arch_auto_shutdown();
#else
	/* Ensure that interrupts are disabled */
	irq_disable();

	/* Make sure that PVR and Maple are shut down */
	pvr_shutdown();
	maple_shutdown();

	/* Shut down any other hardware things */
	hardware_shutdown();
#endif

	if (__kos_init_flags & INIT_MALLOCSTATS) {
		malloc_stats();
	}

	/* Shut down IRQs */
	irq_shutdown();
}

/* Generic kernel exit point (configurable) */
void arch_exit() {
	switch (arch_exit_path) {
	default:
		dbglog(DBG_CRITICAL, "arch: arch_exit_path has invalid value!\n");
	case ARCH_EXIT_RETURN:
		arch_return();
		break;
	case ARCH_EXIT_MENU:
		arch_menu();
		break;
	case ARCH_EXIT_REBOOT:
		arch_shutdown();
		arch_reboot();
		break;
	}
}

/* Called to shut down the system and return to the debug handler (if any) */
void arch_return() {
	/* Shut down */
	arch_shutdown();
	
	/* Jump back to the boot loader */
	arch_real_exit();
}

/* Called to jump back to the BIOS menu; assumes a normal shutdown is possible */
void arch_menu() {
	/* Shut down */
	arch_shutdown();

	/* Jump to the menus */
	dbglog(DBG_CRITICAL, "arch: exiting the system to the BIOS menu\n");

	{ void (*menu)(int) __noreturn; ((uint32 *)menu) = *((uint32 *)0x8c0000e0); menu(1); }
}

/* Called to shut down non-gracefully; assume the system is in peril
   and don't try to call the dtors */
void arch_abort() {
	/* Turn off UBC breakpoints, if any */
	ubc_disable_all();
	
	dbglog(DBG_CRITICAL, "arch: aborting the system\n");

	/* PVR disable-by-fire */
	PVR_SET(PVR_RESET, PVR_RESET_ALL);
	PVR_SET(PVR_RESET, PVR_RESET_NONE);

	/* Maple disable-by-fire */
	maple_dma_stop();

	/* Sound disable (nothing weird done in here) */
	spu_disable();

	/* Turn off any IRQs */	
	irq_disable();
	
	arch_real_exit();
}

/* Called to reboot the system; assume the system is in peril and don't
   try to call the dtors */
void arch_reboot() {
	dbglog(DBG_CRITICAL, "arch: rebooting the system\n");

	/* Ensure that interrupts are disabled */
	irq_disable();

	/* Reboot */
	{ void (*rb)() __noreturn; ((uint32*)rb) = (uint32 *)0xa0000000; rb(); }
}

/* When you make a function called main() in a GCC program, it wants
   this stuff too. */
void _main() { }

/* And some library funcs from newlib want this */
int __errno;

