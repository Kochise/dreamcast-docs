/* sh4sim.c 
 * (c)2000 Dan Potter
 *
 * Basic SH4-only simulator. This thing currently assumes well-written
 * code (hehe), which means that it won't cause things like bus errors
 * and exceptions on purpose.
 *
 * Rather than try to be a complete self-sufficient simulator, it relies
 * on some program hooks to work properly, such as a read-memory callback.
 * This is more closely aligned with libopcodes.
 *
 * Also, this is pretty primitive -- user mode isn't supported, and neither
 * are most of the system devices. And it's not just blazing saddles ;-)
 */
 
#include <string.h>
#include <stdio.h>
#include "sh4sim.h"

/************************************************************************/

/* The register state of the "machine" */
sh4regs_t regs;

/* The breakpoint list; any element in here that's -1 is an empty
 * breakpoint (not assigned). Otherwise it's an address. Since these
 * are unsigned ints, -1 is 0xffffffff.
 */
uint32 breakpoints[MAX_BREAKPOINTS];

/* The read memory callback */
mem_callback_t	read_mem_callback = NULL;

/* The write memory callback */
mem_callback_t	write_mem_callback = NULL;

/************************************************************************/

/* Special reads and writes -- deals with system registers. For now these do
   basically nothing. */
int sim_read_special(uint32 addr, uint32 len, uint8* buffer) {
	uint32 a7 = addr & (~0xe0000000);
	DEBUG("address %08x, %d bytes\n", addr, len);
	if (a7 == 0x1f000010) {		/* mmucr */
		memcpy(buffer, &regs.mmucr, 4);
		return SIME_OK;
	} else if (a7 == 0x1f00001c) {	/* ccr */
		memcpy(buffer, &regs.ccr, 4);
		return SIME_OK;
	} else if (a7 == 0x1f000024) {	/* expevt */
		memcpy(buffer, &regs.expevt, 4);
		return SIME_OK;
	} else if ((a7 & 0xffff0000) == 0x1f800000) {
		return read_mem_callback(addr, len, buffer);
	} else
		return SIME_OK;
}
int sim_write_special(uint32 addr, uint32 len, uint8* buffer) {
	uint32 a7 = addr & (~0xe0000000);
	DEBUG("address %08x, %d bytes\n", addr, len);
	if (a7 == 0x1f000010) {		/* mmucr */
		memcpy(&regs.mmucr, buffer, 4);
		return SIME_OK;
	} else if (a7 == 0x1f00001c) {	/* ccr */
		memcpy(&regs.ccr, buffer, 4);
		return SIME_OK;
	} else if (a7 == 0x1f000024) {	/* expevt */
		memcpy(&regs.expevt, buffer, 4);
		return SIME_OK;
	} else if ((a7 & 0xffff0000) == 0x1f800000) {
		return write_mem_callback(addr, len, buffer);
	} else
		return SIME_OK;
}

/* Reads a memory location. If the memory location is a "special" location
   (i.e., CPU system register), it will be dealt with in read_special. 
   Otherwise, it's sent on to the callback. */
int sim_read(uint32 addr, uint32 len, uint8* buffer) {
	if ((addr & 0xff000000) == 0xf0000000) {	/* Cache read */
	}
	else if ((addr & 0xff000000) == 0xff000000) {	/* P4 Register read */
		return sim_read_special(addr, len, buffer);
	}
	else if ((addr & 0xff000000) == 0x1f000000) {	/* Area 7 Register read */
		return sim_read_special(addr, len, buffer);
	}
	else {						/* Normal/mmap read */
		return read_mem_callback(addr, len, buffer);
	}
}

/* Writes a memory location. If the memory location is a "special" location
   (i.e., CPU system register), it will be dealt with in write_special.
   Otherwise, it's sent on to the callback. */
int sim_write(uint32 addr, uint32 len, uint8* buffer) {
	if ((addr & 0xff000000) == 0xf0000000) {	/* Cache write */
	}
	else if ((addr & 0xff000000) == 0xff000000) {	/* P4 Register write */
		return sim_write_special(addr, len, buffer);
	}
	else if ((addr & 0xff000000) == 0x1f000000) {	/* Area 7 Register write */
		return sim_write_special(addr, len, buffer);
	}
	else {						/* Normal/mmap write */
		return write_mem_callback(addr, len, buffer);
	}
}


/************************************************************************/
/* Gets things rolling in the simulator, returns a status code */
int sim_init(mem_callback_t read, mem_callback_t write) {
	int i;

	read_mem_callback = read;
	write_mem_callback = write;
	
	/* No breakpoints */
	for (i=0; i<MAX_BREAKPOINTS; i++)
		breakpoints[i] = ADDR_NONE;
	
	/* Start out with a blank slate */
	memset(&regs, 0, sizeof(sh4regs_t));

	/* Start in register bank 0 */
	regs.rbank = regs.rbanks[0];

	/* Start us out with a stack */
	regs.r[15] = 0x8d000000;		/* At top of RAM */
	
	/* Now initialize system default values */
	regs.bcr2 = 0x3ffc;
	regs.wcr1 = 0x77777777;
	regs.wcr2 = 0xfffeefff;
	regs.tcor0 = regs.tcnt0 = 0xffffffff;
	regs.tcor1 = regs.tcnt1 = 0xffffffff;
	regs.tcor2 = regs.tcnt2 = 0xffffffff;
	
	return SIME_OK;
}

/* Starts executing at 'pc', or at the currently stored pc if 'pc' 
   here is ADDR_NONE. Execution will stop when an exception happens.
   The returned value from sim_exec_single() will be returned. */
int sim_execute(uint32 pc) {
	int rv;
	
	if (pc == ADDR_NONE)
		pc = regs.pc;
	else
		regs.pc = pc;
	
	// DEBUG("start executing code at %08x\n", pc);
	do {
		rv = sim_exec_single();
	} while (rv == SIME_OK);
	return rv;
}

/* Executes one instruction at 'pc', or at the currently stored pc if
   'pc' here is ADDR_NONE. After execution, the resulting pc will be
   saved into the stored registers. */
int sim_step(uint32 pc) {
	if (pc == 0xffffffff)
		pc = regs.pc;
	else
		regs.pc = pc;
	return sim_exec_single();
}



