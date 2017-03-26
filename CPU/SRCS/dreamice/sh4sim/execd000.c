/* Opcodes dxxx -- one mov

   Output from GDB's 'gencode -t':
   1101nnnni8p4.... mov.l @(<disp>,PC),<REG_N>    

*/

#include "sh4sim.h"

int sim_exec_d000(uint16 instr) {
	int imm = instr & 0x00ff;
	int rn = i0f00;
	uint32 ea = (regs.pc & 0xfffffffc) + 4 + imm*4;
	DEBUG("pc %08x, imm %4x, ea %08x\n", regs.pc, imm, ea);
	sim_next_pc();
	return sim_read(ea, 4, (uint8*)&regs.r[rn]);
}
