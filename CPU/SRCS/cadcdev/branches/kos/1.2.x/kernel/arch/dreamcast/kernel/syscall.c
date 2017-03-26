/* KallistiOS ##version##

   syscall.c
   (c)2001 Dan Potter
*/

/* In KOS-MMU, this was used to enter the kernel from a user-mode
   program. In KOS 1.1.x and above, the same ideas (if not the same
   routines) will be used to ensure that any kernel-level routine
   like synchronization and threading is running in a protected
   kernel setting (interrupts disabled, context saved, etc).

   Basically what happens is that some routine that wants exclusive
   access to the kernel and potentially wants to reschedule the
   running threads will call the macro SYSCALL(). SYSCALL()
   merely executes a trap and then jumps to the routine specified
   in the call. The routine should execute the "RETURN" or
   "SET_RETURN" macro and then return normally (potentially
   calling thd_schedule() in between if neccessary). */

#include <arch/types.h>
#include <arch/irq.h>
#include <arch/syscall.h>

CVSID("$Id");

/* The actual syscall handler */
static vuint32 * const tra = (uint32*)0xff000020;
extern void syscall_entry(irq_t source, irq_context_t *context);
/* R3 will contain the address to which we should jump. When that
   routine returns, we will context switch back into the original
   caller (or some other scheduled thread). Called routines can
   pass up to four parameters in R4 - R7. */
asm(
"_syscall_entry:\n"
"	mov.l	@(12,r5),r3\n"
"	mov.l	@(16,r5),r4\n"
"	mov.l	@(24,r5),r6\n"
"	mov.l	@(28,r5),r7\n"
"	jmp	@r3\n"
"	mov.l	@(20,r5),r5\n"
);

/* Set the return value for a syscall for a dormant thread */
void syscall_set_return(irq_context_t *context, int value) {
	context->r[0] = value;
}

/* Init routine */
int syscall_init() {
	/* Hook the IRQ handler for trapa */
	return trapa_set_handler(0, syscall_entry);
}

/* Shutdown */
void syscall_shutdown() {
	/* Unhook the IRQ handler */
	trapa_set_handler(0, NULL);
}





