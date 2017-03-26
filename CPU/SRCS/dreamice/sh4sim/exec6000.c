/* Opcodes 6xxx -- mov's and a few extensions, and logical not

   Output from GDB's 'gencode -t':

0110nnnnmmmm0000 mov.b @<REG_M>,<REG_N>        // implemented (jrd)
0110nnnnmmmm0001 mov.w @<REG_M>,<REG_N>        // implemented (jrd)
0110nnnnmmmm0010 mov.l @<REG_M>,<REG_N>        // implemented (jrd)
0110nnnnmmmm0011 mov <REG_M>,<REG_N>           // implemented
0110nnnnmmmm0100 mov.b @<REG_M>+,<REG_N>       // implemented (jrd)
0110nnnnmmmm0101 mov.w @<REG_M>+,<REG_N>       // implemented (jrd)
0110nnnnmmmm0110 mov.l @<REG_M>+,<REG_N>       // implemented (jrd)
0110nnnnmmmm0111 not <REG_M>,<REG_N>           // implemented (jrd)
0110nnnnmmmm1000 swap.b <REG_M>,<REG_N>        // implemented (jrd)
0110nnnnmmmm1001 swap.w <REG_M>,<REG_N>        // implemented (check impl tho)
0110nnnnmmmm1010 negc <REG_M>,<REG_N>          // implemented (check impl tho) (jrd)
0110nnnnmmmm1011 neg <REG_M>,<REG_N>           // implemented (jrd)
0110nnnnmmmm1100 extu.b <REG_M>,<REG_N>        // implemented (jrd)
0110nnnnmmmm1101 extu.w <REG_M>,<REG_N>        // implemented (jrd)
0110nnnnmmmm1110 exts.b <REG_M>,<REG_N>        // implemented (jrd)
0110nnnnmmmm1111 exts.w <REG_M>,<REG_N>        // implemented (jrd)

*/

#include "sh4sim.h"

/* mov.b @<REG_M>,<REG_N> */
int exec_6000(uint16 instr) {
	uint32 ea = regs.r[i00f0];
	sim_read_and_check(ea, 1, (uint8*)&regs.r[i0f00]);
	sim_next_pc();
	sim_sign_extend_byte(&regs.r[i0f00]);
	return SIME_OK;
}

/* mov.w @<REG_M>,<REG_N> */
int exec_6001(uint16 instr) {
	uint32 ea = regs.r[i00f0];
	sim_read_and_check(ea, 2, (uint8*)&regs.r[i0f00]);
	sim_next_pc();
	sim_sign_extend_word(&regs.r[i0f00]);
	return SIME_OK;
}

/* mov.l @<REG_M>,<REG_N> */
int exec_6002(uint16 instr) {
	uint32 ea = regs.r[i00f0];
	sim_read_and_check(ea, 4, (uint8*)&regs.r[i0f00]);
	sim_next_pc();
	return SIME_OK;
}

/* mov <REG_M>,<REG_N> */
int exec_6003(uint16 instr) {
	int rm = i00f0;
	int rn = i0f00;
	regs.r[rn] = regs.r[rm];
	sim_next_pc();
	return SIME_OK;
}

/* mov.b @<REG_M>+,<REG_N> */
int exec_6004(uint16 instr) {
	uint32 ea = regs.r[i00f0];
	sim_read_and_check(ea, 1, (uint8*)&regs.r[i0f00]);
	sim_next_pc();
	sim_sign_extend_byte(&regs.r[i0f00]);
	if (i00f0 != i0f00)
		regs.r[i00f0] += 1;
	return SIME_OK;
}

/* mov.w @<REG_M>+,<REG_N> */
int exec_6005(uint16 instr) {
	uint32 ea = regs.r[i00f0];
	sim_read_and_check(ea, 2, (uint8*)&regs.r[i0f00]);
	sim_next_pc();
	sim_sign_extend_word(&regs.r[i0f00]);
	if (i00f0 != i0f00)
		regs.r[i00f0] += 2;
	return SIME_OK;
}

/* mov.l @<REG_M>+,<REG_N> */
int exec_6006(uint16 instr) {
	uint32 ea = regs.r[i00f0];
	sim_read_and_check(ea, 4, (uint8*)&regs.r[i0f00]);
	sim_next_pc();
	if (i00f0 != i0f00)
		regs.r[i00f0] += 4;
	return SIME_OK;
}

/* not <REG_M>,<REG_N> */
int exec_6007(uint16 instr) {
	regs.r[i0f00] = ~regs.r[i00f0];
	sim_next_pc();
	return SIME_OK;
}

/* swap.b <REG_M>,<REG_N> */
int exec_6008(uint16 instr) {
	uint32 topword = 0xFFFF0000 & regs.r[i00f0];
	uint32 botword = 0x0000FFFF & regs.r[i00f0];
	regs.r[i0f00] = topword | ((botword & 0x00FF) << 8) | ((botword & 0xFF00) >> 8);
	sim_next_pc();
	return SIME_OK;
}

/* swap.w <REG_M>,<REG_N> */
int exec_6009(uint16 instr) {
	int rm = i00f0;
	int rn = i0f00;
	regs.r[rn] = ((regs.r[rm] & 0xffff) << 16)
		| ((regs.r[rm] >> 16) & 0xffff);
	sim_next_pc();
	return SIME_OK;
}

/* negc <REG_M>,<REG_N> */
int exec_600a(uint16 instr) {
	int32 tmp = 0 - regs.r[i00f0];
	regs.r[i0f00] = tmp - (regs.sr & SR_T_MASK);
	if (0 < tmp)
		regs.sr |= SR_T_MASK;
	else
		regs.sr &= ~SR_T_MASK;
	if (tmp < regs.r[i0f00])
		regs.sr |= SR_T_MASK;
	sim_next_pc();
	return SIME_OK;
}

/* neg <REG_M>,<REG_N> */
int exec_600b(uint16 instr) {
	regs.r[i0f00] = 0 - regs.r[i00f0];
	sim_next_pc();
	return SIME_OK;
}

/* extu.b <REG_M>,<REG_N> */
int exec_600c(uint16 instr) {
	regs.r[i0f00] = regs.r[i00f0];
	regs.r[i0f00] &= 0x000000FF;
	sim_next_pc();
	return SIME_OK;
}

/* extu.w <REG_M>,<REG_N> */
int exec_600d(uint16 instr) {
	regs.r[i0f00] = regs.r[i00f0];
	regs.r[i0f00] &= 0x0000FFFF;
	sim_next_pc();
	return SIME_OK;
}

/* exts.b <REG_M>,<REG_N> */
int exec_600e(uint16 instr) {
	regs.r[i0f00] = regs.r[i00f0];
	sim_sign_extend_byte(&regs.r[i0f00]);
	sim_next_pc();
	return SIME_OK;
}

/* exts.w <REG_M>,<REG_N> */
int exec_600f(uint16 instr) {
	regs.r[i0f00] = regs.r[i00f0];
	sim_sign_extend_word(&regs.r[i0f00]);
	sim_next_pc();
	return SIME_OK;
}

sim_func funcs_6000[] = {
	exec_6000,
	exec_6001,
	exec_6002,
	exec_6003,
	exec_6004,
	exec_6005,
	exec_6006,
	exec_6007,
	exec_6008,
	exec_6009,
	exec_600a,
	exec_600b,
	exec_600c,
	exec_600d,
	exec_600e,
	exec_600f
};

int sim_exec_6000(uint16 instr) {
	sim_func func = funcs_6000[i000f];
	return func(instr);
}
