/* KallistiOS ##version##

   arch/ps2/kernel/irq.c
   (c)2002 Dan Potter
*/

/* This module contains low-level handling for IRQs and related exceptions. */

#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <arch/irq.h>
#include <arch/cache.h>
#include <ps2/ioports.h>
#include <arch/dbgio.h>
#include <arch/arch.h>

/* Exception table */
static irq_handler irq_handlers[0x100];

/* INTC table */
static irq_handler intc_handlers[0x10];

/* Global exception handler -- hook this if you want to get each and every
   exception; you might get more than you bargained for, but it can be useful. */
static irq_handler irq_hnd_global;

/* Default IRQ context location (until threading is up) */
static irq_context_t irq_context_default;

/* Are we inside an interrupt? */
static int inside_int;
int irq_inside_int() {
	return inside_int;
}

/* Set a handler, or remove a handler */
int irq_set_handler(irq_t code, irq_handler hnd) {
	if ((code & 0xff) == EXC_INTR_0) {
		intc_handlers[(code >> 8) & 0xff] = hnd;
	} else {
		irq_handlers[code & 0xff] = hnd;
	}
	return 0;
}

/* Get the address of the current handler */
irq_handler irq_get_handler(irq_t code) {
	if ((code & 0xff) == EXC_INTR_0) {
		return intc_handlers[(code >> 8) & 0xff];
	} else {
		return irq_handlers[code & 0xff];
	}
}

/* Set a global handler */
int irq_set_global_handler(irq_handler hnd) {
	irq_hnd_global = hnd;
	return 0;
}

/* Get the global exception handler */
irq_handler irq_get_global_handler() {
	return irq_hnd_global;
}

/* Print a kernel panic reg dump */
extern irq_context_t *irq_srt_addr;
void irq_dump_regs(int code, int evt) {
	dbglog(DBG_DEAD, "Unhandled exception\n");
}

/* IRQ save-regs table (in entry.S) */
extern irq_context_t *irq_srt_addr;

/* The C-level routine that processes context switching and other
   types of interrupts. Note: we are running on the stack of the
   process that was interrupted! */
volatile uint32 jiffies = 0;
void irq_handle_exception() {
	int	i, vtype, exccode, idx;
	uint32	is;

	inside_int = 1;

	/* Dig the vector type out of k1 */
	vtype = (CONTEXT_128_TO_32(irq_srt_addr->r[27]) << 4) & 0xf0;

	/* Get ExcCode */
	exccode = (irq_srt_addr->cause >> 2) & 0x0f;

	/* Put those two together to get the exception index */
	idx = vtype | exccode;

	/* If it was a syscall, then increase PC before returning */
	if (idx == EXC_SYSCALL)
		CONTEXT_128_TO_32(irq_srt_addr->pc) += 4;

	if (vtype == 0x40) {
		/* Interrupt -- call the handlers for any active bits and ack all */
		is = INTC_STAT;
		for (i=0; i<15; i++) {
			if (is & (1<<i)) {
				if (intc_handlers[i])
					intc_handlers[i](idx, irq_srt_addr);
				switch (i) {
				case 9:		/* TIMER0 */
					timer_clear(0); break;
				case 10:	/* TIMER1 */
					timer_clear(1); break;
				case 11:	/* TIMER2 */
					timer_clear(2); break;
				case 12:	/* TIMER3 */
					timer_clear(3); jiffies++; break;
				}
			}
		}
		INTC_STAT = is;
	} else if (irq_handlers[idx]) {
		irq_handlers[idx](idx, irq_srt_addr);
	} else {
		/* Some other type of interrupt which we can't handle... die the
		   hard way */
		dbgio_printf("Unhandled exception type %04x\n", idx);
		arch_exit();
	}

	inside_int = 0;
}

/* Switches register banks; call this outside of exception handling
   (but make sure interrupts are off!!) to change where registers will
   go to, or call it inside an exception handler to switch contexts. 
   Make sure you have at least REG_BYTE_CNT bytes available. DO NOT
   ALLOW ANY INTERRUPTS TO HAPPEN UNTIL THIS HAS BEEN CALLED AT 
   LEAST ONCE! */
void irq_set_context(irq_context_t *regbank) {
	irq_srt_addr = regbank;
}

/* Return the current IRQ context */
irq_context_t *irq_get_context() {
	return irq_srt_addr;
}

/* Fill a newly allocated context block for usage with supervisor/kernel
   or user mode. The given parameters will be passed to the called routine (up
   to the architecture maximum). */
void irq_create_context(irq_context_t *context, ptr_t stkpntr,
	ptr_t routine, uint64 *args, int usermode)
{
	int i;

	/* We don't support user mode at this point */
	assert( usermode == 0 );

	/* Clear out the context */
	memset(context, 0, sizeof(irq_context_t));

	/* Copy all of these regs from the current context (we should probably
	   do something a bit more intelligent here, but this ought to do for now) */
	context->status = irq_srt_addr->status;
	context->cause = irq_srt_addr->cause;
	context->config = irq_srt_addr->config;
	context->badvaddr = irq_srt_addr->badvaddr;
	context->badpaddr = irq_srt_addr->badpaddr;
	context->fcr31 = irq_srt_addr->fcr31;

	/* Initialize the PC and stack */
	CONTEXT_PC(*context) = routine;
	CONTEXT_SP(*context) = stkpntr;

	/* Copy up to 4 args */
	for (i=0; i<4; i++) {
		CONTEXT_128_TO_32(context->r[4+i]) = args[i];
	}
}

/* Are we initted? */
static int initted = 0;

/* Refs to our exception vector templates */
extern void _ps2ev_tlb_refill(), _ps2ev_counter(), _ps2ev_debug(), _ps2ev_common(),
	_ps2ev_interrupt();

/* A default syscall implementation for testing */
#if 0
static void irq_sc_def(irq_t src, irq_context_t * cxt) {
	/* Syscall -- Toggle the internal LED for the amusement of the user */
	int i, j, k, type;
	type = (src >> 4) & 0x0f;
	for (i=0; i<5; i++) {
		for (j=0; j<type+1; j++) {
			PIO_DIR = PIO_DIR_OUT;
			PIO_DATA = PIO_DATA_LED_ON;
			for (k=0; k<2500000; k++)
				;
			PIO_DIR = PIO_DIR_OUT;
			PIO_DATA = PIO_DATA_LED_OFF;
			for (k=0; k<2500000; k++)
				;
		}
		for (k=0; k<10000000; k++)
			;
	}
	if (src == EXC_SYSCALL)
		cxt->pc += 4;
}
#endif

/* Init */
int irq_init() {
	if (initted)
		return 0;

	/* Default to not in an interrupt */
	inside_int = 1;

	/* Setup a default SRT location */
	irq_set_context(&irq_context_default);

	/* Start out with no handlers */
	memset(irq_handlers, 0, sizeof(irq_handlers));
	memset(intc_handlers, 0, sizeof(intc_handlers));

	/* Load new IRQ handlers */
	memcpy((void *)0x80000000, &_ps2ev_tlb_refill, 0x80);
	memcpy((void *)0x80000080, &_ps2ev_counter, 0x80);
	memcpy((void *)0x80000100, &_ps2ev_debug, 0x80);
	memcpy((void *)0x80000180, &_ps2ev_common, 0x80);
	memcpy((void *)0x80000200, &_ps2ev_interrupt, 0x80);
	cache_flush_all();

	/* Start out with no INTC interrupts enabled */
	INTC_MASK = INTC_MASK;
	INTC_STAT = 0x7fff;

	/* Set a default syscall */
	// irq_set_handler(EXC_SYSCALL, irq_sc_def);

	initted = 1;

	return 0;
}

/* Shutdown */
void irq_shutdown() {
	/* No need to reset our IRQ handlers, startup.S will do it. */
	initted = 0;
	irq_disable();
	INTC_STAT = 0x7fff;
	INTC_MASK = INTC_MASK;
}
