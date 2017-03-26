/* Opcodes axxx -- one branch instruction

   Output from GDB's 'gencode -t':
   1010i12......... bra <bdisp12>                 

*/

#include "sh4sim.h"

int sim_exec_a000(uint16 instr) {
	int imm = (instr & 0x0fff);
	uint32 newpc, dpc = regs.pc + 2;
	if (imm & 0x800)
		imm |= 0xfffff000;
	else
		imm &= 0x00000fff;
	newpc = regs.pc + imm * 2 + 4;
	
	if (newpc == regs.pc) {
		DEBUG("branch calls itself\n",0);
		return SIME_ERROR;
	}
	
	sim_next_pc_is(newpc);
	sim_exec_delay(dpc);
	return SIME_OK;
}
