/* Opcodes 5xxx -- a single mov instruction 

   Output from GDB's 'gencode -t':
   0101nnnnmmmmi4*4 mov.l @(<disp>,<REG_M>),<REG_N>

*/

#include "sh4sim.h"

int sim_exec_5000(uint16 instr) {
	int imm = i000f;
	int rm = i00f0;
	int rn = i0f00;
	int ea = regs.r[rm] + imm*4;
	sim_next_pc();
	return sim_read(ea, 4, (uint8*)&regs.r[rn]);
}
