/* KallistiOS ##version##

   arch/ia32/kernel/irq.c
   Copyright (c)2003 Dan Potter
*/
      
#include <errno.h>
#include <string.h>
#include <arch/irq.h>
#include <arch/dbgio.h>
#include <kos/process.h>

// Exception table. This table matches an exception/IRQ to a function
// pointer and a process handle. If the pointer is null, then nothing
// happens. Otherwise, the function will handle the exception.
static irq_handler irq_handlers[0x102];
static kprocess_t * irq_handlers_procs[0x102];

// Global exception handler -- hook this if you want to get each and every
// exception; you might get more than you bargained for, but it can be useful.
static irq_handler irq_hnd_global;
static kprocess_t * irq_hnd_global_proc;

// Default IRQ context location
static irq_context_t irq_context_default;

// Defined in the asm file: what's our current context?
extern irq_context_t * irq_srt_addr;

// Are we inside an interrupt?
static int inside_int;
int irq_inside_int() {
	return inside_int;
}

// List of strings for CPU faults
static const char * faultnames[] = {
	"Divide error",
	"Debug",
	"Nonmaskable Interrupt",
	"Breakpoint",
	"Overflow",
	"Bound",
	"Invalid opcode",
	"Device not available",
	"Double fault",
	"Coprocessor overrun",
	"Invalid TSS",
	"Segment not present",
	"Stack fault",
	"General protection fault",
	"Page fault",
	"Reserved",
	"Coprocessor Error"
};

// Do a little debug dump of the current task.
void irq_dump_regs(int code, uint32 errcode) {
	irq_context_t * t = irq_srt_addr;

	dbgio_printf("Unhandled exception: EIP %08lx, code %d error %08lx\n", t->eip, code, errcode);
	if (code >= 0 && code <= 16) {
		dbgio_printf("%s\n", faultnames[code]);
	}
	dbgio_printf(" EAX %08lx  EBX %08lx  ECX %08lx  EDX %08lx\n", t->eax, t->ebx, t->ecx, t->edx);
	dbgio_printf(" ESI %08lx  EDI %08lx  EBP %08lx  ESP %08lx\n", t->esi, t->edi, t->ebp, t->esp);
	dbgio_printf(" EFLAGS %08lx\n", t->eflags);
	if (thd_current) {
		dbgio_printf("Died in thread %d\n", thd_current->tid);
		if (thd_current->pshell) {
			dbgio_printf("Which is in process %d (base %p)\n", thd_current->pshell->pid,
				thd_current->pshell->image.data);
		}
	}
	// arch_stk_trace_at(t->ebp, 0);
}

// C-Level interrupt/exception handler. NOTE: We are running on the stack
// of the thread that was interrupted!
void irq_handle_exception(int code, uint32 errcode) {
	int handled = 0;

	// Nested exception?
	if (inside_int) {
		irq_handler hnd = irq_handlers[EXC_DOUBLE_FAULT];
		if (hnd != NULL)
			hnd(EXC_DOUBLE_FAULT, irq_srt_addr);
		else
			irq_dump_regs(code, errcode);
		thd_pslist(dbgio_printf);
		process_print_list(dbgio_printf);
		panic("double fault");
	}
	inside_int = 1;

	// If there's a global handler, call it
	if (irq_hnd_global) {
		irq_hnd_global(code, irq_srt_addr);
		handled = 1;
	}

	// If there's a handler, call it
	{
		irq_handler hnd = irq_handlers[code];
		if (hnd != NULL) {
			hnd(code, irq_srt_addr);
			handled = 1;
		}
	}

	// Did it get handled?
	if (!handled) {
		irq_handler hnd = irq_handlers[EXC_UNHANDLED_EXC];
		if (hnd != NULL)
			hnd(code, irq_srt_addr);
		else
			irq_dump_regs(code, errcode);
		panic("unhandled IRQ/Exception");
	}

	inside_int = 0;
}

// Set or remove a handler
int _irq_set_handler(kprocess_t * proc, irq_t src, irq_handler hnd) {
	int old;

	// Make sure they don't do something crackheaded
	if (src > 0x102) {
		errno = EINVAL;
		return -1;
	}

	old = irq_disable();

	irq_handlers[src] = hnd;
	irq_handlers_procs[src] = proc;

	irq_restore(old);
	
	return 0;
}

// Get a handler
irq_handler irq_get_handler(irq_t source) {
	// Make sure they don't do something crackheaded
	if (source > 0x102) {
		errno = EINVAL;
		return NULL;
	}

	return irq_handlers[source];
}

// Set or remove global handler
int _irq_set_global_handler(struct kprocess * proc, irq_handler hnd) {
	int old;

	old = irq_disable();

	irq_hnd_global = hnd;
	irq_hnd_global_proc = proc;

	irq_restore(old);
	return 0;
}

// Get global handler
irq_handler irq_get_global_handler() {
	return irq_hnd_global;
}

void irq_create_context(irq_context_t *context, ptr_t stkpntr,
	ptr_t routine, uint32 *args, int usermode)
{
	uint32	* stk;

	// Clear out the struct to start with
	memset(context, 0, sizeof(irq_context_t));

	// Start the task with interrupts enabled
	context->eflags = 1 << 9;

	// Setup the program frame
	context->eip = routine;
	context->ebp = 0xffffffff;

	// Copy the program args onto the stack
	stk = (uint32 *)stkpntr;
	stk--; *stk = args[3];
	stk--; *stk = args[2];
	stk--; *stk = args[1];
	stk--; *stk = args[0];
	stk--; *stk = 0;	// Bogus ret addr
	context->esp = (uint32)stk;
}

void irq_set_context(irq_context_t *regbank) {
	irq_srt_addr = regbank;
}

irq_context_t * irq_get_context() {
	return irq_srt_addr;
}

void irq_remove_process(struct kprocess * proc) {
	int old, i;

	old = irq_disable();

	for (i=0; i<0x100; i++) {
		if (irq_handlers_procs[i] == proc) {
			irq_handlers[i] = NULL;
			irq_handlers_procs[i] = NULL;
		}
	}

	if (irq_hnd_global_proc == proc) {
		irq_hnd_global = NULL;
		irq_hnd_global_proc = NULL;
	}

	irq_restore(old);
}

int irq_init() {
	// Make sure interrupts are disabled
	irq_disable();

	// Blank the exception handler tables
	memset(irq_handlers, 0, sizeof(irq_handlers));
	memset(irq_handlers_procs, 0, sizeof(irq_handlers_procs));
	irq_hnd_global = NULL;
	irq_hnd_global_proc = NULL;

	// Default to not inside an int
	inside_int = 0;

	// Set a default context (will be superceded if threads are
	// enabled later)
	irq_set_context(&irq_context_default);

	// Do the low-level setup to get us hooked into an IDT
	irq_low_setup();

	return 0;
}

void irq_shutdown() {
	// Disable interrupts
	irq_disable();
}
