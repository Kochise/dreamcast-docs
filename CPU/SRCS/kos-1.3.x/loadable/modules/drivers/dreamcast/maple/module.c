#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <dc/maple.h>
#include <dc/maple/controller.h>
#include <arch/arch.h>
#include <kos/exports.h>
#include <sys/process.h>
#include <sys/module.h>
#include <kos/sem.h>

extern export_sym_t maple_symtab[];
static symtab_handler_t ms = {
	{ "sym/maple",
	  0,
	  0x00010000,
	  0,
	  NMMGR_TYPE_SYMTAB,
	  NMMGR_LIST_INIT },
	maple_symtab
};

int module_init(int argc, char **argv) {
	printf("maple: initializing\n");

	maple_init();
	maple_wait_scan();
	nmmgr_handler_add(&ms.nmmgr);
	cont_btn_callback(0, CONT_START | CONT_A | CONT_B | CONT_X | CONT_Y, arch_abort);
	
	printf("maple: done initializing\n");

	return 0;
}

int module_shutdown() {
	printf("maple: exiting\n");

	nmmgr_handler_remove(&ms.nmmgr);
	maple_shutdown();

	return 0;
}

int main(int argc, char **argv) {
	return kos_do_module(module_init, module_shutdown, argc, argv);
}
