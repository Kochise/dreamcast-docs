/* KallistiOS ##version##

   arch/ia32/kernel/init.c
   Copyright (c)2003 Dan Potter
*/

#include <string.h>
#include <arch/arch.h>
#include <arch/dbgio.h>
#include <arch/irq.h>
#include <arch/timer.h>
//#include <sys/process.h>
//#include <kos/mm.h>
#include <kos/nmmgr.h>
#include <kos/fs.h>
#include <kos/fs_romdisk.h>
#include <kos/fs_pty.h>
#include <kos/net.h>

void arch_abort() {
	dbgio_printk("Halted.\n");
	asm("cli");
	asm("hlt");
}

void arch_reboot() {
}

void arch_exit() {
	arch_abort();
}

void arch_remove_process(kprocess_t * proc) {
	irq_remove_process(proc);
}

extern const char banner[];
extern uint8 edata, end;
int main(int argc, char **argv);

int arch_main() {
	// Clear out BSS
	uint8 *bss_start = (uint8 *)(&edata);
	uint8 *bss_end = (uint8 *)(&end);
	memset(bss_start, 0, bss_end - bss_start);

	// Ensure we pull in crtend.c
	__crtend_pullin();

	// Print out a welcome banner
	dbgio_init();
	if (__kos_init_flags & INIT_QUIET) {
		dbgio_set_printk(dbgio_null_write);
	} else {
		dbgio_printk("\n--\n");
		dbgio_printk(banner);
	}

	// Initialize memory management
	mm_init();

	// Setup hardware basics
	irq_init();
	dbgio_init_2();
	timer_init();
	timer_ms_enable();
	rtc_init();

	// Switch on interrupts
	irq_enable();

	// Threads
	if (__kos_init_flags & INIT_THD_PREEMPT)
		thd_init(THD_MODE_PREEMPT);
	else
		thd_init(THD_MODE_COOP);

	// Mark a few regions unusable (thanks IBM!)
	// XXX Can't do this anymore, need to use the MMU.
	// mm_palloc(0x000a0000, 0x60000/PAGESIZE, _local_process);

	// VFS facilities
	nmmgr_init();
	fs_init();
	fs_romdisk_init();
	fs_pty_init();

	if (__kos_romdisk != NULL) {
		fs_romdisk_mount("/rd", __kos_romdisk);
	}

	// Enable IRQs to start the whole shebang rolling
	if (__kos_init_flags & INIT_IRQ)
		irq_enable();

	// Enable networking
	net_init();

	// Run ctors
	arch_ctors();

	// Call main.
	main(0, NULL);

	// Call kernel exit.
	arch_exit();

	return 0;
}
