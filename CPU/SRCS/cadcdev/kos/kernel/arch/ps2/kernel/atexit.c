/* KallistiOS ##version##

   atexit.c
   (c)2002 Florian Schulze
*/

#include <arch/arch.h>
#include <arch/atexit.h>
#include <malloc.h>
#include <stdio.h>

CVSID("$Id: atexit.c,v 1.1 2002/10/26 08:04:00 bardtx Exp $");

/* atexit() handling

   Note: we may eventually move this into libc */

struct arch_atexit_handler *arch_atexit_handlers = NULL;

void atexit(void (*func)(void)) {
	struct arch_atexit_handler *new_handler;

	if (!func)
		return;
	
	new_handler = malloc(sizeof(struct arch_atexit_handler));
	if (!new_handler)
		return; /* TODO: error handling? */
	
	new_handler->handler = func;
	new_handler->next = arch_atexit_handlers;
	
	arch_atexit_handlers = new_handler;
}

/* Call all the atexit() handlers */
void arch_atexit() {
	struct arch_atexit_handler *exit_handler;

	dbglog(DBG_CRITICAL, "arch: calling atexit functions\n");

	exit_handler = arch_atexit_handlers;
	while (exit_handler) {
		if (exit_handler->handler)
			exit_handler->handler();
		
		exit_handler = exit_handler->next;
		free(arch_atexit_handlers);
		arch_atexit_handlers = exit_handler;
	}
}


