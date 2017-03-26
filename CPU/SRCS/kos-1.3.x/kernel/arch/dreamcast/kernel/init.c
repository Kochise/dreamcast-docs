/* KallistiOS ##version##

   main.c
   Copyright (C)2000,2001,2002,2003 Dan Potter
*/

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <arch/dbgio.h>
#include <arch/timer.h>
#include <arch/arch.h>
#include <arch/atexit.h>
#include <arch/irq.h>
#include <arch/rtc.h>
#include <dc/ubc.h>
#include <dc/asic.h>
#include <dc/vblank.h>
#include <kos/nmmgr.h>

#include "initall_hdrs.h"

CVSID("$Id: init.c,v 1.4 2003/08/02 23:34:00 bardtx Exp $");

extern int _bss_start, end;

/* This really ought to be prototyped in a header */
int	mm_init();

/* Ditto */
int	main(int argc, char **argv);

/* Double-ditto */
extern const char banner[];

int arch_auto_init() {
	dbgio_printk_func old;

//	if (!(__kos_init_flags & INIT_NO_DCLOAD))
//		fs_dcload_init_console();	/* Init dc-load console, if applicable */
	dbgio_init();			/* Init debug IO and print a banner */
	if (__kos_init_flags & INIT_QUIET)
		dbgio_set_printk(dbgio_null_write);
	else {
		// PTYs not initialized yet
		dbgio_printk("\n--\n");
		dbgio_printk(banner);
	}
	
	/* Initialize memory management */
	mm_init();

	irq_init();			/* IRQs */
	irq_disable();			/* Turn on exceptions */
	timer_init();			/* Timers */
	hardware_sys_init();		/* DC low-level hardware init */

	/* Initialize our timer */
	timer_ms_enable();
	rtc_init();

	/* Threads */
	if (__kos_init_flags & INIT_THD_PREEMPT)
		thd_init(THD_MODE_PREEMPT);
	else
		thd_init(THD_MODE_COOP);

	nmmgr_init();

	fs_init();			/* VFS */
	fs_romdisk_init();		/* Romdisk */
	fs_pty_init();			/* Pty */

	if (__kos_romdisk != NULL) {
		fs_romdisk_mount("/rd", __kos_romdisk);
	}
/*	if (!(__kos_init_flags & INIT_NO_DCLOAD) && *DCLOADMAGICADDR == DCLOADMAGICVALUE) {
		dbglog(DBG_INFO, "dc-load console support enabled\n");
		fs_dcload_init();
	} */

	/* Now comes the optional stuff */
	if (__kos_init_flags & INIT_IRQ)
		irq_enable();		/* Turn on IRQs */

	net_init();		/* Enable networking (and drivers) */

	return 0;
}

void arch_auto_shutdown() {
	irq_disable();
	timer_shutdown();
	hardware_shutdown();
	net_shutdown();
	fs_pty_shutdown();
	fs_romdisk_shutdown();
	fs_shutdown();
	nmmgr_shutdown();
	thd_shutdown();
	rtc_shutdown();
}

void arch_remove_process(struct kprocess * proc) {
	irq_remove_process(proc);
	asic_remove_process(proc);
	vblank_remove_process(proc);
}

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
	_atexit_call_all();
	arch_dtors();

	dbglog(DBG_CRITICAL, "arch: shutting down kernel\n");

	/* Turn off UBC breakpoints, if any */
	ubc_disable_all();
	
	/* Do auto-shutdown */
	arch_auto_shutdown();

/*	if (__kos_init_flags & INIT_MALLOCSTATS) {
		malloc_stats();
	} */

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

	/* XXX We probably need to do something with these again so aborts
	   are graceful! */
	/* PVR disable-by-fire */
	/* PVR_SET(PVR_RESET, PVR_RESET_ALL);
	PVR_SET(PVR_RESET, PVR_RESET_NONE); */

	/* Maple disable-by-fire */
	// maple_dma_stop();

	/* Sound disable (nothing weird done in here) */
	// spu_disable();

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

