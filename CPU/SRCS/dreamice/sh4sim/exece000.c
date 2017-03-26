/* Opcodes exxx -- one mov

   Output from GDB's 'gencode -t':
   1110nnnni8*1.... mov #<imm>,<REG_N>            

*/

#include "sh4sim.h"

int sim_exec_e000(uint16 instr) {
	int imm = instr & 0x00ff;
	int rn = i0f00;
	regs.r[rn] = imm;
	sim_sign_extend_byte(&regs.r[rn]);
	sim_next_pc();
	return SIME_OK;
}
