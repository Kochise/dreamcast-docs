/* Opcodes 3xxx -- A few compares and div/mul's, oVerflow operations

   All of the code in this file is a bit sketchy thanks to the bizarre
   pseudo-code in the Hitachi PDF. A lot of it needs to be redone with
   int64's and uint64's for clarity. div1 is especially suspect.

   Output from GDB's 'gencode -t':

0011nnnnmmmm0000 cmp/eq <REG_M>,<REG_N>        // implemented
0011nnnnmmmm0010 cmp/hs <REG_M>,<REG_N>        // implemented
0011nnnnmmmm0011 cmp/ge <REG_M>,<REG_N>        // implemented
0011nnnnmmmm0100 div1 <REG_M>,<REG_N>          // implemented... I think
0011nnnnmmmm0101 dmulu.l <REG_M>,<REG_N>       // implemented
0011nnnnmmmm0110 cmp/hi <REG_M>,<REG_N>        // implemented
0011nnnnmmmm0111 cmp/gt <REG_M>,<REG_N>        // implemented
0011nnnnmmmm1000 sub <REG_M>,<REG_N>           // implemented
0011nnnnmmmm1010 subc <REG_M>,<REG_N>          // implemented
0011nnnnmmmm1011 subv <REG_M>,<REG_N>          // implemented
0011nnnnmmmm1100 add <REG_M>,<REG_N>           // implemented
0011nnnnmmmm1101 dmuls.l <REG_M>,<REG_N>       // implemented
0011nnnnmmmm1110 addc <REG_M>,<REG_N>          // implemented
0011nnnnmmmm1111 addv <REG_M>,<REG_N>          // implemented
  
*/
#include "sh4sim.h"

/* cmp/xx <REG_M>,<REG_N>
0011nnnnmmmm0000 cmp/eq <REG_M>,<REG_N>        
0011nnnnmmmm0010 cmp/hs <REG_M>,<REG_N>        
0011nnnnmmmm0011 cmp/ge <REG_M>,<REG_N>        
0011nnnnmmmm0110 cmp/hi <REG_M>,<REG_N>        
0011nnnnmmmm0111 cmp/gt <REG_M>,<REG_N> */
int exec_3000_cmp(uint16 instr) {
	int t;
	uint32 rnu = regs.r[i0f00];
	uint32 rmu = regs.r[i00f0];
	int32 rns = *((int32*)&regs.r[i0f00]);
	int32 rms = *((int32*)&regs.r[i00f0]);
	switch (i000f) {
		case 0:		/* /eq */
			t = rnu == rmu;
			break;
		case 2:		/* /hs */
			t = rnu >= rmu;
			break;
		case 3:		/* /ge */
			t = rns >= rms;
			break;
		case 6:		/* /hi */
			t = rnu > rmu;
			break;
		case 7:		/* /gt */
			t = rns > rms;
			break;
		default:
			return sim_exec_unimpl(instr);
	}
	regs.sr = (regs.sr & ~SR_T_MASK);
	if (t) regs.sr |= SR_T_MASK;
	sim_next_pc();
	return SIME_OK;
}

/* div1 <REG_M>,<REG_N>: from PDF... EVIL!!! */
/* This code is STUPID. There has gotta be a better way to do this once
   I stop being lazy and optimize it. */
int exec_3004(uint16 instr) {
	uint32 rm = regs.r[i00f0];
	uint32 rn = regs.r[i0f00];
	uint32 tmp0, tmp2;
	uint32 old_q, tmp1;
	
	old_q = regs.sr & SR_Q_MASK;
	if ((0x80000000 & rn) != 0)
		regs.sr |= SR_Q_MASK;
	else
		regs.sr &= SR_Q_MASK;
	tmp2 = rm;
	rn <<= 1;
	if (regs.sr & SR_T_MASK)
		rn |= 1;
	
	if (old_q == 0) {
		if ((regs.sr & SR_M_MASK) == 0) {
			tmp0 = rn;
			rn -= tmp2;
			tmp1 = (rn > tmp0);
			if ((regs.sr & SR_Q_MASK) == 0) {
				if (tmp1)
					regs.sr |= SR_Q_MASK;
				else
					regs.sr &= ~SR_Q_MASK;
			} else {
				if (tmp1)
					regs.sr &= ~SR_Q_MASK;
				else
					regs.sr |= SR_Q_MASK;
			}
		} else {
			tmp0 = rn;
			rn += tmp2;
			tmp1 = (rn < tmp0);
			if ((regs.sr & SR_Q_MASK) == 0) {
				if (tmp1)
					regs.sr &= ~SR_Q_MASK;
				else
					regs.sr |= SR_Q_MASK;
			} else {
				if (tmp1)
					regs.sr |= SR_Q_MASK;
				else
					regs.sr &= ~SR_Q_MASK;
			}
		}
	} else {
		if ((regs.sr & SR_M_MASK) == 0) {
			tmp0 = rn;
			rn += tmp2;
			tmp1 = (rn < tmp0);
			if ((regs.sr & SR_Q_MASK) == 0) {
				if (tmp1)
					regs.sr |= SR_Q_MASK;
				else
					regs.sr &= ~SR_Q_MASK;
			} else {
				if (tmp1)
					regs.sr &= ~SR_Q_MASK;
				else
					regs.sr |= SR_Q_MASK;
			}
		} else {
			tmp0 = rn;
			rn -= tmp2;
			tmp1 = (rn > tmp0);
			if ((regs.sr & SR_Q_MASK) == 0) {
				if (tmp1)
					regs.sr &= ~SR_Q_MASK;
				else
					regs.sr |= SR_Q_MASK;
			} else {
				if (tmp1)
					regs.sr |= SR_Q_MASK;
				else
					regs.sr &= ~SR_Q_MASK;
			}
		}
	}
	
	tmp0 = (regs.sr & SR_Q_MASK) != 0;
	tmp1 = (regs.sr & SR_M_MASK) != 0;
	if (tmp0 == tmp1)
		regs.sr |= SR_T_MASK;
	else
		regs.sr &= ~SR_T_MASK;
	
	regs.r[i00f0] = rm;
	regs.r[i0f00] = rn;

	sim_next_pc();
	return SIME_OK;
}

/* dmulu.l <REG_M>,<REG_N> */
int exec_3005(uint16 instr) {
	uint64 rn = (uint64)regs.r[i0f00];
	uint64 rm = (uint64)regs.r[i00f0];
	uint64 result = rn * rm;
	regs_mac_set(result);
	sim_next_pc();
	return SIME_OK;
}

/* sub <REG_M>,<REG_N> */
int exec_3008(uint16 instr) {
	regs.r[i0f00] = regs.r[i0f00] - regs.r[i00f0];
	sim_next_pc();
	return SIME_OK;
}

/* subc <REG_M>,<REG_N>: from PDF */
int exec_300a(uint16 instr) {
	uint32 rn = regs.r[i0f00];
	uint32 rm = regs.r[i00f0];
	uint32 tmp0, tmp1;
	int t;
	
	if (regs.sr & SR_T_MASK)
		t = 1;
	else
		t = 0;
	
	tmp1 = rn - rm;
	tmp0 = rn;
	rn = tmp1 - t;
	if (tmp0 < tmp1)
		t = 1;
	else
		t = 0;
	if (tmp1 < rn)
		t = 1;
	
	if (t)
		regs.sr |= SR_T_MASK;
	else
		regs.sr &= ~SR_T_MASK;
	
	regs.r[i0f00] = rn;
	regs.r[i00f0] = rm;
	sim_next_pc();
	return SIME_OK;
}

/* subv <REG_M>,<REG_N>, from PDF */
int exec_300b(uint16 instr) {
	int32 dest, src, ans;
	int32 rn = *((int32*)&regs.r[i0f00]);
	int32 rm = *((int32*)&regs.r[i00f0]);
	
	if (rn >= 0)
		dest = 0;
	else
		dest = 1;
	if (rm >= 0)
		src = 0;
	else
		src = 1;
	src += dest;
	rn -= rm;
	if (rn >= 0)
		ans = 0;
	else
		ans = 1;
	ans += dest;
	if (src == 1) {
		if (ans == 1)
			regs.sr |= SR_T_MASK;
		else
			regs.sr &= ~SR_T_MASK;
	} else {
		regs.sr &= ~SR_T_MASK;
	}
	
	*((int32*)&regs.r[i0f00]) = rn;
	*((int32*)&regs.r[i00f0]) = rm;
	sim_next_pc();
	return SIME_OK;
}

/* add <REG_M>,<REG_N> */
int exec_300c(uint16 instr) {
	regs.r[i0f00] += regs.r[i00f0];
	sim_next_pc();
	return SIME_OK;
}

/* dmuls.l <REG_M>,<REG_N> */
int exec_300d(uint16 instr) {
	int32 rn = *((int32*)&regs.r[i0f00]);
	int32 rm = *((int32*)&regs.r[i00f0]);
	int64 result = rn * rm;
	regs_mac_set(*((uint64*)&result));
	sim_next_pc();
	return SIME_OK;
}

/* addc <REG_M>,<REG_N>, from PDF */
int exec_300e(uint16 instr) {
	uint32 tmp0, tmp1;
	uint32 rn = regs.r[i0f00];
	uint32 rm = regs.r[i00f0];
	int t;
	
	if (regs.sr & SR_T_MASK)
		t = 1;
	else
		t = 0;
	
	tmp1 = rn + rm;
	tmp0 = rn;
	rn = tmp1 + t;
	if (tmp0 > tmp1)
		t = 1;
	else
		t = 0;
	if (tmp1 > rn)
		t = 1;
	
	regs.r[i0f00] = rn;
	regs.r[i00f0] = rm;
	if (t)
		regs.sr |= SR_T_MASK;
	else
		regs.sr &= ~SR_T_MASK;
	
	sim_next_pc();
	return SIME_OK;
}

/* addv <REG_M>,<REG_N>, from PDF */
int exec_300f(uint16 instr) {
	int32 dest, src, ans;
	int32 rn = *((int32*)&regs.r[i0f00]);
	int32 rm = *((int32*)&regs.r[i00f0]);
	
	if (rn >= 0)
		dest = 0;
	else
		dest = 1;
	if (rm >= 0)
		src = 0;
	else
		src = 1;
	src += dest;
	rn += rm;
	if (rn >= 0)
		ans = 0;
	else
		ans = 1;
	ans += dest;
	if (src == 0 || src == 2) {
		if (ans == 1)
			regs.sr |= SR_T_MASK;
		else
			regs.sr &= ~SR_T_MASK;
	} else {
		regs.sr &= ~SR_T_MASK;
	}
	
	*((int32*)&regs.r[i0f00]) = rn;
	*((int32*)&regs.r[i00f0]) = rm;
	sim_next_pc();
	return SIME_OK;
}


sim_func funcs_3000[] = {
	exec_3000_cmp,
	sim_exec_unimpl,
	exec_3000_cmp,
	exec_3000_cmp,
	exec_3004,
	exec_3005,
	exec_3000_cmp,
	exec_3000_cmp,
	exec_3008,
	sim_exec_unimpl,
	exec_300a,
	exec_300b,
	exec_300c,
	exec_300d,
	exec_300e,
	exec_300f
};


int sim_exec_3000(uint16 instr) {
	sim_func func = funcs_3000[i000f];
	return func(instr);
}


