/* Opcodes 8xxx -- Branches, a compare, and *gasp* more mov's 

   Output from GDB's 'gencode -t':

10001011i8p1.... bf <bdisp8>                   // implemented (jrd)
10001111i8p1.... bf.s <bdisp8>                 // implemented (jrd)
10001001i8p1.... bt <bdisp8>                   // implemented (jrd)
10001101i8p1.... bt.s <bdisp8>                 // implemented (jrd)
10001000i8*1.... cmp/eq #<imm>,R0              // implemented (jrd)
10000000mmmmi4*1 mov.b R0,@(<disp>,<REG_M>)    // implemented
10000001mmmmi4*2 mov.w R0,@(<disp>,<REG_M>)    // implemented
10000100mmmmi4*1 mov.b @(<disp>,<REG_M>),R0    // implemented
10000101mmmmi4*2 mov.w @(<disp>,<REG_M>),R0    // implemented

*/

#include "sh4sim.h"

/* mov.b R0,@(<disp>,<REG_M>) */
int exec_8000(uint16 instr) {
	uint32 ea = regs.r[i00f0] + i000f;
	sim_next_pc();
	return sim_write(ea, 1, (uint8*)&regs.r[0]);
}

/* mov.w R0,@(<disp>,<REG_M>) */
int exec_8100(uint16 instr) {
	uint32 ea = regs.r[i00f0] + i000f*2;
	sim_next_pc();
	return sim_write(ea, 2, (uint8*)&regs.r[0]);
}

/* mov.b @(<disp>,<REG_M>),R0 */
int exec_8400(uint16 instr) {
	uint32 ea = regs.r[i00f0] + i000f;
	sim_read_and_check(ea, 1, (uint8*)&regs.r[0]);
	sim_sign_extend_byte(&regs.r[0]);
	sim_next_pc();
	return SIME_OK;
}

/* mov.w @(<disp>,<REG_M>),R0 */
int exec_8500(uint16 instr) {
	uint32 ea = regs.r[i00f0] + i000f*2;
	sim_read_and_check(ea, 2, (uint8*)&regs.r[0]);
	sim_sign_extend_word(&regs.r[0]);
	sim_next_pc();
	return SIME_OK;
}

/* cmp/eq #<imm>,R0 */
int exec_8800(uint16 instr) {
	int32 tmp = instr & 0x00ff;
	sim_sign_extend_word(&tmp);
	if (regs.r[0] == tmp)
		regs.sr |= SR_T_MASK;
	else
		regs.sr &= SR_T_MASK;
	sim_next_pc();
	return SIME_OK;
}

/* bt <bdisp8> */
int exec_8900(uint16 instr) {
	int32 disp = instr & 0x00ff;
	uint32 dpc = regs.pc + 2;

	if (regs.sr & SR_T_MASK) {
		sim_sign_extend_byte((uint32*)&disp);
		sim_next_pc_is(regs.pc + 4 + disp * 2);
	} else {
		sim_next_pc();
	}

	return SIME_OK;
}

/* bf <bdisp8> */
int exec_8b00(uint16 instr) {
	int32 disp = instr & 0x00ff;
	uint32 dpc = regs.pc + 2;

	if (!(regs.sr & SR_T_MASK)) {
		sim_sign_extend_byte((uint32*)&disp);
		sim_next_pc_is(regs.pc + 4 + disp * 2);
	} else {
		sim_next_pc();
	}

	return SIME_OK;
}

/* bt.s <bdisp8> */
int exec_8d00(uint16 instr) {
	int32 disp = instr & 0x00ff;
	uint32 dpc = regs.pc + 2;

	if (regs.sr & SR_T_MASK) {
		sim_sign_extend_byte((uint32*)&disp);
		sim_exec_delay(dpc);
		sim_next_pc_is(regs.pc + 4 + disp * 2);
	} else {
		sim_next_pc();
	}

	return SIME_OK;
}

/* bf.s <bdisp8> */
int exec_8f00(uint16 instr) {
	int32 disp = instr & 0x00ff;
	uint32 dpc = regs.pc + 2;

	if (!(regs.sr & SR_T_MASK)) {
		sim_sign_extend_byte((uint32*)&disp);
		sim_exec_delay(dpc);
		sim_next_pc_is(regs.pc + 4 + disp * 2);
	} else {
		sim_next_pc();
	}

	return SIME_OK;
}

sim_func funcs_8000[] = {
	exec_8000,
	exec_8100,
	sim_exec_unimpl,
	sim_exec_unimpl,
	exec_8400,
	exec_8500,
	sim_exec_unimpl,
	sim_exec_unimpl,
	exec_8800,
	exec_8900,
	sim_exec_unimpl,
	exec_8b00,
	sim_exec_unimpl,
	exec_8d00,
	sim_exec_unimpl,
	exec_8f00
};

int sim_exec_8000(uint16 instr) {
	sim_func func = funcs_8000[i0f00];
	return func(instr);
}



