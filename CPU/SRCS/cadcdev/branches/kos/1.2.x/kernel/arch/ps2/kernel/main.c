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

#include "initall_hdrs.h"

CVSID("$Id: main.c,v 1.4 2002/11/06 08:36:00 bardtx Exp $");

/* This really ought to be prototyped in a header */
int	mm_init();

/* Ditto */
int	main(int argc, char **argv);

/* Double-ditto */
extern const char banner[];

/* For some reason, the linker won't pull in _start() from startup.o
   unless you explicitly link to it, even though it'll give an error
   about a missing _start. -_- */
void _start();
void __help_dumb_compiler__() {
	_start();
}

/* Auto-init stuff: comment out here if you don't like this stuff
   to be running in your build, and also below in arch_main() */
/* #if 0 */
int arch_auto_init() {
	dbgio_init();			/* Init debug IO and print a banner */
	fs_ps2load_init_console();
	dbglog(DBG_INFO, "\n--\n");
	dbglog(DBG_INFO, banner);

	timer_init();			/* Timers */
	irq_init();			/* IRQs */
	syscall_init();			/* System call interface */
#if 0	
	hardware_init();		/* DC Hardware init */
#endif

	/* Threads */
#if 0
	if (__kos_init_flags & INIT_THD_PREEMPT)
		thd_init(THD_MODE_PREEMPT);
	else
#endif
		thd_init(THD_MODE_COOP);

	fs_init();			/* VFS */
	fs_ramdisk_init();		/* Ramdisk */
	fs_romdisk_init();		/* Romdisk */

	if (__kos_romdisk != NULL) {
		fs_romdisk_mount("/rd", __kos_romdisk, 0);
	}
	if (fs_ps2load_init() >= 0) {
		dbglog(DBG_INFO, "ps2-load console support enabled\n");
	}
#if 0
	fs_iso9660_init();
	fs_vmu_init();

	/* Now comes the optional stuff */
	if (__kos_init_flags & INIT_IRQ) {
		irq_enable();		/* Turn on IRQs */
		maple_wait_scan();	/* Wait for the maple scan to complete */
	}
	if (__kos_init_flags & INIT_NET) {
		net_init();		/* Enable networking (and drivers) */
	}

	/* And one more mandatory thing */
	timer_ms_enable();
#endif

	return 0;
}

void arch_auto_shutdown() {
	irq_disable();
	timer_shutdown();
#if 0
	snd_shutdown();
	hardware_shutdown();
	net_shutdown();
	pvr_shutdown();
	fs_dcload_shutdown();
	fs_vmu_shutdown();
	fs_iso9660_shutdown();
#endif
	fs_ramdisk_shutdown();
	fs_romdisk_shutdown();
	fs_shutdown();
	thd_shutdown();
}
/* #endif */

/* This is the entry point inside the C program */
void arch_main() {
	int rv;

	/* Ensure that we pull in crtend.c in the linking process */
	__crtend_pullin();

	/* Ensure that UBC is not enabled from a previous session */
	// ubc_disable_all();

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
}

/* Set the exit path (default is RETURN) */
int arch_exit_path = ARCH_EXIT_RETURN;
void arch_set_exit_path(int path) {
	assert(path == ARCH_EXIT_RETURN);
	arch_exit_path = path;
}

/* Does the actual shutdown stuff for a proper shutdown */
void arch_shutdown() {
	/* Run dtors */
	arch_atexit();
	arch_dtors();

	dbglog(DBG_CRITICAL, "arch: shutting down kernel\n");

	/* Turn off UBC breakpoints, if any */
	// ubc_disable_all();
	
	/* Do auto-shutdown... or use the "light weight" version underneath */
#if 1
	arch_auto_shutdown();
#else
	/* Ensure that interrupts are disabled */
	irq_disable();
	irq_enable_exc();

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
	// irq_shutdown();
}

/* Generic kernel exit point (configurable) */
void arch_exit() {
	/* switch (arch_exit_path) {
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
	} */
	arch_return();
}

/* Called to shut down the system and return to the debug handler (if any) */
void arch_return() {
	/* Shut down */
	arch_shutdown();
	
	/* Jump back to the boot loader */
	arch_real_exit();
}

/* Called to shut down non-gracefully; assume the system is in peril
   and don't try to call the dtors */
void arch_abort() {
	/* Turn off UBC breakpoints, if any */
	// ubc_disable_all();
	
	dbglog(DBG_CRITICAL, "arch: aborting the system\n");

#if 0
	/* PVR disable-by-fire */
	PVR_SET(PVR_RESET, PVR_RESET_ALL);
	PVR_SET(PVR_RESET, PVR_RESET_NONE);

	/* Maple disable-by-fire */
	maple_dma_stop();

	/* Sound disable (nothing weird done in here) */
	spu_disable();

	/* Turn off any IRQs */	
	irq_disable();
#endif

	arch_real_exit();
}

/* When you make a function called main() in a GCC program, it wants
   this stuff too. */
void _main() { }

/* And some library funcs from newlib want this */
int __errno;

