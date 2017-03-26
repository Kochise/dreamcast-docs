/* Opcodes 4xxx -- Shifts (a few) and a lot of system/control register stuff

   Output from GDB's 'gencode -t':
   
0100nnnn01010010 sts.l FPUL,@-<REG_N>          // implemented
0100nnnn01100010 sts.l FPSCR,@-<REG_N>         // implemented
0100nnnn00000010 sts.l MACH,@-<REG_N>          // implemented
0100nnnn00010010 sts.l MACL,@-<REG_N>          // implemented
0100nnnn00100010 sts.l PR,@-<REG_N>            // implemented
0100nnnn10000010 stc R0_BANK,@-<REG_N>         // implemented
0100nnnn10010010 stc R1_BANK,@-<REG_N>         // implemented
0100nnnn10100010 stc R2_BANK,@-<REG_N>         // implemented
0100nnnn10110010 stc R3_BANK,@-<REG_N>         // implemented
0100nnnn11000010 stc R4_BANK,@-<REG_N>         // implemented
0100nnnn11010010 stc R5_BANK,@-<REG_N>         // implemented
0100nnnn11100010 stc R6_BANK,@-<REG_N>         // implemented
0100nnnn11110010 stc R7_BANK,@-<REG_N>         // implemented
0100nnnn00000011 stc.l SR,@-<REG_N>            // implemented
0100nnnn00010011 stc.l GBR,@-<REG_N>           // implemented
0100nnnn00100011 stc.l VBR,@-<REG_N>           // implemented
0100nnnn00110011 stc.l SSR,@-<REG_N>           // implemented
0100nnnn01000011 stc.l SPC,@-<REG_N>           // implemented
0100nnnn00000110 lds.l @<REG_N>+,MACH          // implemented
0100nnnn00010110 lds.l @<REG_N>+,MACL          // implemented
0100nnnn00100110 lds.l @<REG_N>+,PR            // implemented
0100nnnn01010110 lds.l @<REG_N>+,FPUL          // implemented
0100nnnn01100110 lds.l @<REG_N>+,FPSCR         // implemented
0100nnnn00000111 ldc.l @<REG_N>+,SR            // implemented
0100nnnn00010111 ldc.l @<REG_N>+,GBR           // implemented
0100nnnn00100111 ldc.l @<REG_N>+,VBR           // implemented
0100nnnn00110111 ldc.l @<REG_N>+,SSR           // implemented
0100nnnn01000111 ldc.l @<REG_N>+,SPC           // implemented
0100nnnn10000111 ldc.l @<REG_N>+,R0_BANK       // implemented
0100nnnn10010111 ldc.l @<REG_N>+,R1_BANK       // implemented
0100nnnn10100111 ldc.l @<REG_N>+,R2_BANK       // implemented
0100nnnn10110111 ldc.l @<REG_N>+,R3_BANK       // implemented
0100nnnn11000111 ldc.l @<REG_N>+,R4_BANK       // implemented
0100nnnn11010111 ldc.l @<REG_N>+,R5_BANK       // implemented
0100nnnn11100111 ldc.l @<REG_N>+,R6_BANK       // implemented
0100nnnn11110111 ldc.l @<REG_N>+,R7_BANK       // implemented
0100nnnn00001010 lds <REG_N>,MACH              // implemented
0100nnnn00011010 lds <REG_N>,MACL              // implemented
0100nnnn00101010 lds <REG_N>,PR                // implemented
0100nnnn01011010 lds <REG_N>,FPUL              // implemented
0100nnnn01101010 lds <REG_N>,FPSCR             // implemented
0100nnnn00001110 ldc <REG_N>,SR                // implemented
0100nnnn00011110 ldc <REG_N>,GBR               // implemented
0100nnnn00101110 ldc <REG_N>,VBR               // implemented
0100nnnn00111110 ldc <REG_N>,SSR               // implemented
0100nnnn01001110 ldc <REG_N>,SPC               // implemented
0100nnnn10001110 ldc <REG_N>,R0_BANK           // implemented
0100nnnn10011110 ldc <REG_N>,R1_BANK           // implemented
0100nnnn10101110 ldc <REG_N>,R2_BANK           // implemented
0100nnnn10111110 ldc <REG_N>,R3_BANK           // implemented
0100nnnn11001110 ldc <REG_N>,R4_BANK           // implemented
0100nnnn11011110 ldc <REG_N>,R5_BANK           // implemented
0100nnnn11101110 ldc <REG_N>,R6_BANK           // implemented
0100nnnn11111110 ldc <REG_N>,R7_BANK           // implemented
0100nnnn00000000 shll <REG_N>                  // implemented
0100nnnn00010000 dt <REG_N>                    // implemented
0100nnnn00100000 shal <REG_N>                  // implemented
0100nnnn00000001 shlr <REG_N>                  // implemented
0100nnnn00010001 cmp/pz <REG_N>                // implemented
0100nnnn00100001 shar <REG_N>                  // implemented
0100nnnn00100100 rotcl <REG_N>                 // implemented
0100nnnn00000100 rotl <REG_N>                  // implemented
0100nnnn00010101 cmp/pl <REG_N>                // implemented
0100nnnn00100101 rotcr <REG_N>                 // implemented
0100nnnn00000101 rotr <REG_N>                  // implemented
0100nnnn00001000 shll2 <REG_N>                 // implemented
0100nnnn00011000 shll8 <REG_N>                 // implemented
0100nnnn00101000 shll16 <REG_N>                // implemented
0100nnnn00001001 shlr2 <REG_N>                 // implemented
0100nnnn00011001 shlr8 <REG_N>                 // implemented
0100nnnn00101001 shlr16 <REG_N>                // implemented
0100nnnn00101011 jmp @<REG_N>                  // implemented
0100nnnn00001011 jsr @<REG_N>                  // implemented
0100nnnn00011011 tas.b @<REG_N>                // implemented
0100nnnnmmmm1100 shad <REG_M>,<REG_N>          // implemented
0100nnnnmmmm1101 shld <REG_M>,<REG_N>          // implemented
0100nnnnmmmm1111 mac.w @<REG_M>+,@<REG_N>+     // implemented

*/

#include "sh4sim.h"

/* dt, shal, shll */
int exec_4000(uint16 instr) {
	switch(i00f0) {
		case 0:		/* shll <REG_N> */
			regs.r[i0f00] <<= 1;
			break;
		case 1:		/* dt <REG_N> */
			regs.r[i0f00]--;
			if (regs.r[i0f00] == 0)
				regs.sr |= SR_T_MASK;
			else
				regs.sr &= ~SR_T_MASK;
			break;
		case 2:		/* shal <REG_N> */
			if (regs.r[i0f00] & 0x80000000)
				regs.sr |= SR_T_MASK;
			else
				regs.sr &= ~SR_T_MASK;
			regs.r[i0f00] <<= 1;
			break;
		default:
			return sim_exec_unimpl(instr);
	}
	
	sim_next_pc();
	return SIME_OK;
}

/* cmp/pz, shlr, shar */
int exec_4001(uint16 instr) {
	switch(i00f0) {
		case 0:		/* shlr <REG_N> */
			regs.r[i0f00] >>= 1;
			break;
		case 1: {		/* cmp/pz <REG_N> */
			int32 r = *((int32*)&regs.r[i0f00]);
			if (r >= 0)
				regs.sr |= SR_T_MASK;
			else
				regs.sr &= ~SR_T_MASK;
			break;
		}
		case 2:		/* shar <REG_N> */
			if (regs.r[i0f00] & 1)
				regs.sr |= SR_T_MASK;
			else
				regs.sr &= ~SR_T_MASK;
			regs.r[i0f00] >>= 1;
			regs.r[i0f00] |= (regs.r[i0f00] << 1) & 0x80000000;
			break;
		default:
			return sim_exec_unimpl(instr);
	}
	
	sim_next_pc();
	return SIME_OK;
}

/* stc/sts Rm,@-<REG_N> */
int exec_4002(uint16 instr) {
	uint32 sgr = 0;
	uint32* srcregs[16] = {
		&regs.mach, &regs.macl, &regs.pr, &sgr, NULL,
		&regs.fpul, &regs.fpscr
	};
	int regidx = i0f00;
	int srcregidx = i00f0;
	uint32 value = *(srcregs[srcregidx]);
	if (srcregidx == 3)
		DEBUG("reading weird reg SGR\n",0);
	regs.r[regidx] -= 4;
	sim_next_pc();
	return sim_write(regs.r[regidx], 4, (uint8*)srcregs[srcregidx]);
}

/* stc Rm,@-<REG_N> */
int exec_4003(uint16 instr) {
	uint32* srcregs[16] = {
		&regs.sr, &regs.gbr, &regs.vbr, &regs.ssr, &regs.spc,
		NULL, NULL, NULL, 
		&regs.rbank[0], &regs.rbank[1], &regs.rbank[2],
		&regs.rbank[3], &regs.rbank[4], &regs.rbank[5],
		&regs.rbank[6]
	};
	regs.r[i0f00] -= 4;
	sim_next_pc();
	return sim_write(regs.r[i0f00], 4, (uint8*)srcregs[i00f0]);
}

/* rotcl, rotl */
int exec_4004(uint16 instr) {
	int tmp;
	
	switch(i00f0) {
		case 0:		/* rotl <REG_N> */
			tmp = (regs.r[i0f00] & 0x80000000) != 0;
			if (tmp)
				regs.sr |= SR_T_MASK;
			else
				regs.sr &= ~SR_T_MASK;
			regs.r[i0f00] = (regs.r[i0f00] << 1) | tmp;
			break;
		case 2:		/* rotcl <REG_N> */
			tmp = (regs.sr & SR_T_MASK) != 0;
			if (regs.r[i0f00] & 0x80000000)
				regs.sr |= SR_T_MASK;
			else
				regs.sr &= ~SR_T_MASK;
			regs.r[i0f00] = (regs.r[i0f00] << 1) | tmp;
			break;
		default:
			return sim_exec_unimpl(instr);
	}
	
	sim_next_pc();
	return SIME_OK;
}

/* cmp/pl, rotcr, rotr */
int exec_4005(uint16 instr) {
	uint32 tmp;
	
	switch(i00f0) {
		case 0:		/* rotr <REG_N> */
			tmp = (regs.r[i0f00] & 1);
			if (tmp)
				regs.sr |= SR_T_MASK;
			else
				regs.sr &= ~SR_T_MASK;
			regs.r[i0f00] = (regs.r[i0f00] >> 1) | (tmp << 31);
			break;
		case 1: {	/* cmp/pl <REG_N> */
			int32 r = *((int32*)&regs.r[i0f00]);
			if (r > 0)
				regs.sr |= SR_T_MASK;
			else
				regs.sr &= ~SR_T_MASK;
			break;
		}
		case 2:		/* rotcr <REG_N> */
			tmp = (regs.sr & SR_T_MASK) != 0;
			if (regs.r[i0f00] & 1)
				regs.sr |= SR_T_MASK;
			else
				regs.sr &= ~SR_T_MASK;
			regs.r[i0f00] = (regs.r[i0f00] >> 1) | (tmp << 31);
			break;
		default:
			return sim_exec_unimpl(instr);
	}
	
	sim_next_pc();
	return SIME_OK;
}

/* lds.l @<REG_N>+,Rm */
int exec_4006(uint16 instr) {
	static uint32* srcregs[16] = {
		&regs.mach, &regs.macl, &regs.pr, NULL, NULL,
		&regs.fpul, &regs.fpscr, NULL, NULL, NULL,
		NULL, NULL, NULL, NULL, NULL, &regs.dbr
	};
	uint32 ea = regs.r[i0f00];
	regs.r[i0f00] += 4;
	sim_next_pc();
	return sim_read(ea, 4, (uint8*)srcregs[i00f0]);
}

/* ldc.l @<REG_N>+,Rm */
int exec_4007(uint16 instr) {
	uint32* srcregs[16] = {
		&regs.sr, &regs.gbr, &regs.vbr, &regs.ssr, &regs.spc,
		NULL, NULL, NULL,
		&regs.rbank[0], &regs.rbank[1], &regs.rbank[2],
		&regs.rbank[2], &regs.rbank[3], &regs.rbank[4],
		&regs.rbank[5], &regs.rbank[6]
	};
	uint32 ea = regs.r[i0f00];
	regs.r[i0f00] += 4;
	sim_next_pc();
	return sim_read(ea, 4, (uint8*)srcregs[i00f0]);
}

/* shllxx <REG_N> */
int exec_4008(uint16 instr) {
	static int stab[16] = {2, 8, 16};
	int sv = stab[((instr & 0x00f0) >> 4)];
	int r = i0f00;
	regs.r[r] <<= sv;
	sim_next_pc();
	return SIME_OK;
}

/* shlrxx <REG_N> */
int exec_4009(uint16 instr) {
	static int stab[16] = {2, 8, 16};
	int sv = stab[i00f0];
	int r = i0f00;
	regs.r[r] >>= sv;
	sim_next_pc();
	return SIME_OK;
}

/* lds <REG_N>,Rm */
int exec_400a(uint16 instr) {
	static uint32* srcregs[16] = {
		&regs.mach, &regs.macl, &regs.pr, NULL, NULL,
		&regs.fpul, &regs.fpscr, NULL, NULL,
		NULL, NULL, NULL, NULL, NULL, NULL, &regs.dbr
	};
	*(srcregs[i00f0]) = regs.r[i0f00];
	sim_next_pc();
	return SIME_OK;
}

/* jmp, jsr, tas.b */
int exec_400b(uint16 instr) {
	switch(i00f0) {
		case 0:		/* jsr @<REG_N> */
			sim_next_pc_is(regs.r[i0f00]);
			regs.pr = regs.pc+4;
			sim_exec_delay(regs.pc + 2);
			break;
		case 1:	{	/* tas.b @<REG_N> */
			/* We ignore the cache stuff here.. all I've got to
			   say about this instruction is.. oooookaaaaayyyy */
			uint32 ea = regs.r[i0f00];
			uint8 data;
			
			sim_read_and_check(ea, 1, &data);
			data |= 0x80;
			sim_write_and_check(ea, 1, &data);
			
			sim_next_pc();
			break;
		}
		case 2:		/* jmp @<REG_N> */
			sim_next_pc_is(regs.r[i0f00]);
			sim_exec_delay(regs.pc + 2);
			break;
	}
	
	return SIME_OK;
}

/* shad <REG_M>,<REG_N>: from PDF */
int exec_400c(uint16 instr) {
	uint32 rm = regs.r[i00f0];
	int sgn = rm & 0x80000000;
	if (sgn == 0)
		regs.r[i0f00] <<= (rm & 0x1f);
	else if ((rm & 0x1f) == 0) {
		if ((regs.r[i0f00] & 0x80000000) == 0)
			regs.r[i0f00] = 0;
		else
			regs.r[i0f00] = 0xFFFFFFFF;
	} else {
		int32 rn = *((int32*)&regs.r[i0f00]);
		rn = rn >> ((~rm & 0x1f) + 1);
		*((int32*)&regs.r[i0f00]) = rn;
	}
	sim_next_pc();
	return SIME_OK;
}

/* shld <REG_M>,<REG_N>: from PDF */
int exec_400d(uint16 instr) {
	uint32 rm = regs.r[i00f0];
	int sgn = rm & 0x80000000;
	if (sgn == 0)
		regs.r[i0f00] <<= (rm & 0x1f);
	else if ((rm & 0x1f) == 0)
		regs.r[i0f00] = 0;
	else
		regs.r[i0f00] >>= ((~rm & 0x1f)+1);
	sim_next_pc();
	return SIME_OK;
}

/* ldc <REG_N>,Rm */
int exec_400e(uint16 instr) {
	uint32* srcregs[16] ={
		&regs.sr, &regs.gbr, &regs.vbr, &regs.ssr, &regs.spc,
		NULL, NULL, NULL,
		&regs.rbank[0], &regs.rbank[1], &regs.rbank[2], &regs.rbank[3], 
		&regs.rbank[4], &regs.rbank[5], &regs.rbank[6], &regs.rbank[7]
	};
	
	*(srcregs[i00f0]) = regs.r[i0f00];
	sim_next_pc();
	return SIME_OK;
}

/* 0100nnnnmmmm1111 mac.w @<REG_M>+,@<REG_N>+     */
int exec_400f(uint16 instr) {
	int16 rn = *((int16*)&regs.r[i0f00]);
	int16 rm = *((int16*)&regs.r[i00f0]);
	int32 result = rn * rm;
	
	if (regs.sr & SR_S_MASK) {
		int64 r = (int64)regs.macl + (int64)result;
		if (r > 0xFFFFFFFFLL) {
			regs.mach |= 1;
			if (r < 0)
				regs.macl = 0x80000000;
			else
				regs.macl = 0x7fffffff;
		}
	} else {
		int64 r = regs_mac + (int64)result;
		regs_mac_set(r);
	}
	sim_next_pc();
	return SIME_OK;
}

sim_func funcs_4000[] = {
	exec_4000,
	exec_4001,
	exec_4002,
	exec_4003,
	exec_4004,
	exec_4005,
	exec_4006,
	exec_4007,
	exec_4008,
	exec_4009,
	exec_400a,
	exec_400b,
	exec_400c,
	exec_400d,
	exec_400e,
	exec_400f
};


int sim_exec_4000(uint16 instr) {
	sim_func func = funcs_4000[i000f];
	return func(instr);
}

