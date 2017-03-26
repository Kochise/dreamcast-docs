/* Opcodes 9xxx -- One mov

   Output from GDB's 'gencode -t':
   1001nnnni8p2.... mov.w @(<disp>,PC),<REG_N>    

*/

#include "sh4sim.h"

int sim_exec_9000(uint16 instr) {
	int imm = instr & 0x00ff;
	int rn = i0f00;
	uint32 ea = regs.pc + 4 + imm*2;
	sim_read_and_check(ea, 2, (uint8*)&regs.r[rn]);
	sim_sign_extend_word(&regs.r[rn]);
	sim_next_pc();
	return SIME_OK;
}
