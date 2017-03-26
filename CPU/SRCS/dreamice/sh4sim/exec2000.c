/* Opcodes 2xxx -- mov's and some div and mul

   Output from GDB's 'gencode -t':

0010nnnnmmmm0000 mov.b <REG_M>,@<REG_N>        // implemented
0010nnnnmmmm0001 mov.w <REG_M>,@<REG_N>        // implemented
0010nnnnmmmm0010 mov.l <REG_M>,@<REG_N>        // implemented
0010nnnnmmmm0100 mov.b <REG_M>,@-<REG_N>       // implemented
0010nnnnmmmm0101 mov.w <REG_M>,@-<REG_N>       // implemented
0010nnnnmmmm0110 mov.l <REG_M>,@-<REG_N>       // implemented
0010nnnnmmmm0111 div0s <REG_M>,<REG_N>         // implemented
0010nnnnmmmm1000 tst <REG_M>,<REG_N>           // implemented
0010nnnnmmmm1001 and <REG_M>,<REG_N>           // implemented
0010nnnnmmmm1010 xor <REG_M>,<REG_N>           // implemented
0010nnnnmmmm1011 or <REG_M>,<REG_N>            // implemented
0010nnnnmmmm1100 cmp/str <REG_M>,<REG_N>       // implemented
0010nnnnmmmm1101 xtrct <REG_M>,<REG_N>         // implemented
0010nnnnmmmm1110 mulu <REG_M>,<REG_N>          // implemented
0010nnnnmmmm1111 muls <REG_M>,<REG_N>          // implemented

*/

#include "sh4sim.h"

/* mov.b <REG_M>,@<REG_N> */
int exec_2000(uint16 instr) {
	int ea = regs.r[i0f00];
	sim_next_pc();
	return sim_write(ea, 1, (uint8*)&regs.r[i00f0]);
}

/* mov.w <REG_M>,@<REG_N> */
int exec_2001(uint16 instr) {
	int ea = regs.r[i0f00];
	sim_next_pc();
	return sim_write(ea, 2, (uint8*)&regs.r[i00f0]);
}

/* mov.l <REG_M>,@<REG_N> */
int exec_2002(uint16 instr) {
	int ea = regs.r[i0f00];
	sim_next_pc();
	return sim_write(ea, 4, (uint8*)&regs.r[i00f0]);
}

/* mov.b <REG_M>,@-<REG_N> */
int exec_2004(uint16 instr) {
	sim_next_pc();
	regs.r[i0f00]--;
	return sim_write(regs.r[i0f00], 1, (uint8*)&regs.r[i00f0]);
}

/* mov.w <REG_M>,@-<REG_N> */
int exec_2005(uint16 instr) {
	sim_next_pc();
	regs.r[i0f00]-=2;
	return sim_write(regs.r[i0f00], 2, (uint8*)&regs.r[i00f0]);
}

/* mov.l <REG_M>,@-<REG_N> */
int exec_2006(uint16 instr) {
	sim_next_pc();
	regs.r[i0f00]-=4;
	return sim_write(regs.r[i0f00], 4, (uint8*)&regs.r[i00f0]);
}

/* div0s <REG_M>,<REG_N> */
int exec_2007(uint16 instr) {
	uint32 rn = regs.r[i0f00];
	uint32 rm = regs.r[i00f0];
	int m, q;
	if (rn & 0x80000000) {
		regs.sr |= SR_Q_MASK;
		q = 1;
	}
	else {
		regs.sr &= ~SR_Q_MASK;
		q = 0;
	}
	if (rm & 0x80000000) {
		regs.sr |= SR_M_MASK;
		m = 1;
	}
	else {
		regs.sr &= ~SR_M_MASK;
		m = 0;
	}
	if (m == q)
		regs.sr &= ~SR_T_MASK;
	else
		regs.sr |= SR_T_MASK;
	sim_next_pc();
	return SIME_OK;
}

/* tst <REG_M>,<REG_N> */
int exec_2008(uint16 instr) {
	if (regs.r[i0f00] & regs.r[i00f0])
		regs.sr &= ~SR_T_MASK;
	else
		regs.sr |= SR_T_MASK;
	sim_next_pc();
	return SIME_OK;
}

/* and <REG_M>,<REG_N> */
int exec_2009(uint16 instr) {
	regs.r[i0f00] &= regs.r[i00f0];
	sim_next_pc();
	return SIME_OK;
}

/* xor <REG_M>,<REG_N> */
int exec_200a(uint16 instr) {
	int rm = i00f0;
	int rn = i0f00;
	regs.r[rn] ^= regs.r[rm];
	sim_next_pc();
	return SIME_OK;
}

/* or <REG_M>,<REG_N> */
int exec_200b(uint16 instr) {
	int rm = i00f0;
	int rn = i0f00;
	regs.r[rn] |= regs.r[rm];
	sim_next_pc();
	return SIME_OK;
}

/* cmp/str <REG_M>,<REG_N>.. thnx PDF */
int exec_200c(uint16 instr) {
	uint32 rm = regs.r[i00f0];
	uint32 rn = regs.r[i0f00];
	uint32 temp, HH, HL, LH, LL;
	temp = rn ^ rm;
	HH=(temp & 0xFF000000) >> 24;
	HL=(temp & 0x00FF0000) >> 16;
	LH=(temp & 0x0000FF00) >> 8;
	LL=(temp & 0x000000FF);
	HH = HH && HL && LH && LL;
	if (HH == 0)
		regs.sr |= SR_T_MASK;
	else
		regs.sr &= ~SR_T_MASK;
	sim_next_pc();
	return SIME_OK;
}

/* xtrct <REG_M>,<REG_N> */
int exec_200d(uint16 instr) {
	uint32 rm = regs.r[i00f0];
	uint32 rn = regs.r[i0f00];
	regs.r[i0f00] = ((rm << 16) & 0xFFFF0000)
		| ((rn >> 16) & 0x0000FFFF);
	sim_next_pc();
	return SIME_OK;
}

/* mulu <REG_M>,<REG_N> */
int exec_200e(uint16 instr) {
	uint32 rm = regs.r[i00f0] & 0x0000FFFF;
	uint32 rn = regs.r[i0f00] & 0xFFFF0000;
	regs.macl = rm * rn;
	sim_next_pc();
	return SIME_OK;
}

/* muls <REG_M>,<REG_N> */
int exec_200f(uint16 instr) {
	int32 rm = regs.r[i00f0] & 0x0000FFFF;
	int32 rn = regs.r[i0f00] & 0x0000FFFF;
	sim_sign_extend_word((uint32*)&rm);
	sim_sign_extend_word((uint32*)&rn);
	*((int32*)regs.macl) = rm * rn;
	return SIME_OK;
}

sim_func funcs_2000[] = {
	exec_2000,
	exec_2001,
	exec_2002,
	sim_exec_unimpl,
	exec_2004,
	exec_2005,
	exec_2006,
	exec_2007,
	exec_2008,
	exec_2009,
	exec_200a,
	exec_200b,
	exec_200c,
	exec_200d,
	exec_200e,
	exec_200f
};

int sim_exec_2000(uint16 instr) {
	sim_func func = funcs_2000[i000f];
	return func(instr);
}

