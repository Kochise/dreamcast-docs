/* Opcodes 7xxx -- one add instruction

   Output from GDB's 'gencode -t':
   0111nnnni8*1.... add #<imm>,<REG_N>            

*/

#include "sh4sim.h"

int sim_exec_7000(uint16 instr) {
	int rn = i0f00;
	int imm = (instr & 0x00ff);
	
	sim_sign_extend_byte((uint32*)&imm);
	
	regs.r[rn] += imm;
	sim_next_pc();
	
	return SIME_OK;
}
