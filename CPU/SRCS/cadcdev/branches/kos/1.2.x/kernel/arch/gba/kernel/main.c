/* KallistiOS ##version##

   main.c
   (c)2001 Dan Potter
*/

static char id[] = "KOS $Id: main.c,v 1.2 2002/09/23 23:03:33 gilm Exp $";

#include <string.h>
#include <kos.h>
#include <kos/fs.h>

/* Auto-init stuff: comment out here if you don't like this stuff
   to be running in your build, and also below in arch_main() */
int arch_auto_init() {

	fs_init();			/* VFS */
//	fs_ramdisk_init();		/* Ramdisk */
	fs_romdisk_init();		/* Romdisk */

	if (__kos_romdisk != NULL) {
		fs_romdisk_mount("/rd", __kos_romdisk, 0);
	}
	
	return 0;
}

/* This is the entry point inside the C program */
int arch_main() {

	if (mm_init() < 0)
		return 0;
		
	arch_auto_init();

	return main(0, NULL);
}

/* Called to shut down the system */
void arch_exit() {
}

/* Called from syscall to reboot the system */
void arch_reboot() {
}


/* When you make a function called main() in a GCC program, it wants
   this stuff too. */
void _main() { }
void atexit() { }

/* GCC 3.0 also wants these */
void __gccmain() { }

