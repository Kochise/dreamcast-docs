/* Opcodes 1xxx -- one lovely instruction =)

   Output from GDB's 'gencode -t':
   0001nnnnmmmmi4*4 mov.l <REG_M>,@(<disp>,<REG_N>)

*/

#include "sh4sim.h"

int sim_exec_1000(uint16 instr) {
	int imm = i000f * 4;
	int rm = i00f0;
	int rn = i0f00;
	int ea = regs.r[rn] + imm;
	sim_next_pc();
	return sim_write(ea, 4, (uint8*)&regs.r[rm]);
}
