#include "sh4sim.h"

/* A default implementation you can call if you don't recognize
   the instruction in your block. */
int sim_exec_unimpl(uint16 instr) {
	DEBUG("unknown instruction %04x\n", instr);
	return SIME_ERROR;
}

/* Performs sign extension for bytes */
void sim_sign_extend_byte(uint32* l) {
	uint8* b = (uint8*)l;
	if (*b & 0x80) {
		*l |= 0xffffff00;
	} else {
		*l &= 0x000000ff;
	}
}

/* Performs sign extension for words */
void sim_sign_extend_word(uint32* l) {
	uint16* w = (uint16*)l;
	if (*w & 0x8000) {
		*l |= 0xffff0000;
	} else {
		*l &= 0x0000ffff;
	}
}

/* Pull in the simulation functions for each opcode block from
   the other exec*.c files. */
sim_func sim_funcs[] = {
	sim_exec_0000,
	sim_exec_1000,
	sim_exec_2000,
	sim_exec_3000,
	sim_exec_4000,
	sim_exec_5000,
	sim_exec_6000,
	sim_exec_7000,
	sim_exec_8000,
	sim_exec_9000,
	sim_exec_a000,
	sim_exec_b000,
	sim_exec_c000,
	sim_exec_d000,
	sim_exec_e000,
	sim_exec_f000
};

/* Executes the single instruction at regs.pc and updates PC. An error code
   is returned. */
int sim_exec_single() {
	uint16 instr;
	sim_func func;
	int rv;
	
	if (sim_read(regs.pc, 2, (uint8*)&instr) != SIME_OK) {
		DEBUG("can't read instruction memory at %08x\n", regs.pc);
		return SIME_ERROR;
	}

	regs.npc = -1;
	
	// DEBUG("\n------- Executing instruction %04x\n", instr);
	func = sim_funcs[(instr >> 12)  & 0x000f];
	rv = func(instr);
	
	if (regs.npc == -1) {
		DEBUG("you forgot to call sim_next_pc() in opcode %04x\n", instr);
		return SIME_ERROR;
	}
	regs.pc = regs.npc;
	
	// DEBUG("\n",0);
	// sim_register_dump();
	
	return rv;
}

/* Executes the single instrunction at dpc and does not update PC. An error code
   is returned. This is wrapped in a macro that does error checking for you. */
int sim_exec_delay_real(uint32 dpc) {
	uint16 instr;
	sim_func func;
	uint32 real_npc;
	int rv;
	
	real_npc = regs.npc;
	if (sim_read(dpc, 2, (uint8*)&instr) != SIME_OK) {
		DEBUG("can't read instruction memory at %08x\n", dpc);
		return SIME_ERROR;
	}

	// DEBUG("Executing delay instruction %04x\n", instr);
	func = sim_funcs[(instr >> 12)  & 0x000f];
	rv = func(instr);
	regs.npc = real_npc;
	return rv;
}

