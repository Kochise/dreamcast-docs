/* KallistiOS ##version##

   syscall.c
   (c)2002 Dan Potter
*/

#include <arch/syscall.h>
#include <arch/irq.h>

CVSID("$Id: syscall.c,v 1.1 2002/11/03 03:40:55 bardtx Exp $");

/* The actual syscall handler */
extern void syscall_entry(irq_t source, irq_context_t *cxt);
/* T0 will contain the address to which we should jump. When that
   routine returns, we will context switch back into the
   original caller (or some other scheduled thread). Called
   routines can pass up to four parameters in A0-A3. */
asm(
"	.text\n"
"syscall_entry:\n"
"	ld	$4,(16*4)($5)\n"	// Load A0
"	ld	$6,(16*6)($5)\n"	// Load A2
"	ld	$7,(16*7)($5)\n"	// Load A3
"	ld	$8,(16*8)($5)\n"	// Load T0
"	jr	$8\n"			// Branch to routine
"	ld	$7,(16*7)($5)\n"	// Load A1
);

/* Set the return value for a syscall for a dormant thread */
void syscall_set_return(irq_context_t *context, int value) {
	CONTEXT_128_TO_32(context->r[2]) = value;
}

/* Init routine */
int syscall_init() {
	/* Hook the IRQ handler for SYSCALL */
	irq_set_handler(EXC_SYSCALL, syscall_entry);
	return 0;
}

/* Shutdown */
void syscall_shutdown() {
	/* Unhook the IRQ handler */
	irq_set_handler(EXC_SYSCALL, NULL);
}
