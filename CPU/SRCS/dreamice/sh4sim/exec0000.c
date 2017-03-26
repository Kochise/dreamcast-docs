/* Opcodes 0xxx -- these are almost all system instructions, and
   so in many cases we just store a value or nop. There are a few
   mov's in here though.
   
   Output from GDB's 'gencode -t':

0000nnnn00000010 stc SR,<REG_N>                // implemented
0000nnnn00010010 stc GBR,<REG_N>               // implemented
0000nnnn00100010 stc VBR,<REG_N>               // implemented
0000nnnn00110010 stc SSR,<REG_N>               // implemented
0000nnnn01000010 stc SPC,<REG_N>               // implemented
0000nnnn10000010 stc R0_BANK,<REG_N>           // implemented
0000nnnn10010010 stc R1_BANK,<REG_N>           // implemented
0000nnnn10100010 stc R2_BANK,<REG_N>           // implemented
0000nnnn10110010 stc R3_BANK,<REG_N>           // implemented
0000nnnn11000010 stc R4_BANK,<REG_N>           // implemented
0000nnnn11010010 stc R5_BANK,<REG_N>           // implemented
0000nnnn11100010 stc R6_BANK,<REG_N>           // implemented
0000nnnn11110010 stc R7_BANK,<REG_N>           // implemented
0000nnnn00100011 braf <REG_N>                  // implemented
0000nnnn00000011 bsrf <REG_N>                  // implemented
0000nnnn11000011 movca.l R0, @<REG_N>          // implemented
0000nnnn10010011 ocbi @<REG_N>                 // no implementation
0000nnnn10100011 ocbp @<REG_N>                 // no implementation
0000nnnn10110011 ocbwb @<REG_N>                // no implementation
0000nnnn10000011 pref @<REG_N>                 // no implementation
0000nnnnmmmm0100 mov.b <REG_M>,@(R0,<REG_N>)   // implemented
0000nnnnmmmm0101 mov.w <REG_M>,@(R0,<REG_N>)   // implemented
0000nnnnmmmm0110 mov.l <REG_M>,@(R0,<REG_N>)   // implemented
0000nnnnmmmm0111 mul.l <REG_M>,<REG_N>         // implemented
0000000000101000 clrmac                        // implemented
0000000001001000 clrs                          // implemented
0000000000001000 clrt                          // implemented
0000000000111000 ldtlb                         // no implementation
0000000001011000 sets                          // implemented
0000000000011000 sett                          // implemented
0000000000011001 div0u                         // implemented
0000nnnn00101001 movt <REG_N>                  // implemented
0000000000001001 nop                           // implemented
0000nnnn01011010 sts FPUL,<REG_N>              // implemented
0000nnnn01101010 sts FPSCR,<REG_N>             // implemented
0000nnnn00001010 sts MACH,<REG_N>              // implemented
0000nnnn00011010 sts MACL,<REG_N>              // implemented
0000nnnn00101010 sts PR,<REG_N>                // implemented
0000000000101011 rte                           // implemented
0000000000001011 rts                           // implemented
0000000000011011 sleep                         // no implementation
0000nnnnmmmm1100 mov.b @(R0,<REG_M>),<REG_N>   // implemented
0000nnnnmmmm1101 mov.w @(R0,<REG_M>),<REG_N>   // implemented
0000nnnnmmmm1110 mov.l @(R0,<REG_M>),<REG_N>   // implemented
0000nnnnmmmm1111 mac.l @<REG_M>+,@<REG_N>+     // implemented (need to check)
  
*/

#include "sh4sim.h"

/* stc CR,<REG_N> */
static exec_0002(uint16 instr) {
	uint32* srcregs[16] = {
		&regs.sr, &regs.gbr, &regs.vbr, &regs.ssr, &regs.spc,
		NULL, NULL, NULL,
		&regs.rbank[0], &regs.rbank[1], &regs.rbank[2],
		&regs.rbank[3], &regs.rbank[4], &regs.rbank[5],
		&regs.rbank[6], &regs.rbank[7]
	};
	int regidx = i0f00;
	int srcregidx = i00f0;
	regs.r[regidx] = *(srcregs[srcregidx]);
	sim_next_pc();
	return SIME_OK;
}
 
/* Several different things */
int exec_0003(uint16 instr) {
	int idx = i00f0;
	int reg = i0f00;
	switch(idx) {
		case 2:	{	/* braf <REG_N> */
			uint32 dpc = regs.pc + 2;
			sim_next_pc_is(regs.r[reg] + 4 + regs.pc);
			sim_exec_delay(dpc);
			return SIME_OK;
		}
		case 0: {	/* bsrf <REG_N> */
			uint32 dpc = regs.pc + 2;
			regs.pr = regs.pc + 4;
			sim_next_pc_is(regs.r[reg] + 4 + regs.pc);
			sim_exec_delay(dpc);
			return SIME_OK;
		}
		case 0x0c:	/* movca.l R0, @<REG_N> -- we ignore cache stuff */
			sim_next_pc();
			return sim_write(regs.r[reg], 4, (uint8*)&regs.r[0]);
		default:	/* Cache instructions */
			sim_next_pc();
			return SIME_OK;
	}
}

/* mov.b <REG_M>,@(R0,<REG_N>) */
int exec_0004(uint16 instr) {
	uint32 ea = regs.r[0] + regs.r[i0f00];
	sim_next_pc();
	return sim_write(ea, 1, (uint8*)&regs.r[i00f0]);
}

/* mov.w <REG_M>,@(R0,<REG_N>) */
int exec_0005(uint16 instr) {
	uint32 ea = regs.r[0] + regs.r[i0f00];
	sim_next_pc();
	return sim_write(ea, 2, (uint8*)&regs.r[i00f0]);
}

/* mov.l <REG_M>,@(R0,<REG_N>) */
int exec_0006(uint16 instr) {
	uint32 ea = regs.r[0] + regs.r[i0f00];
	sim_next_pc();
	return sim_write(ea, 4, (uint8*)&regs.r[i00f0]);
}

/* mul.l <REG_M>,<REG_N> */
int exec_0007(uint16 instr) {
	regs.macl = regs.r[i0f00] * regs.r[i00f0];
	sim_next_pc();
	return SIME_OK;
}

/* Various sets/clears for SR */
int exec_0008(uint16 instr) {
	switch(i00f0) {
		case 0:		/* clrt */
			regs.sr &= ~SR_T_MASK;
			break;
		case 1:		/* sett */
			regs.sr |= SR_T_MASK;
			break;
		case 2:		/* clrmac */
			regs.macl = regs.mach = 0;
			break;
		case 3:		/* ldtlb */
			/* nop: we don't support MMU right now */
			break;
		case 4:		/* clrs */
			regs.sr &= ~SR_S_MASK;
			break;
		case 5:		/* sets */
			regs.sr |= SR_S_MASK;
			break;
		default:
			return sim_exec_unimpl(instr);
	}
	sim_next_pc();
	return SIME_OK;
}

/* div0u, movt, nop */
int exec_0009(uint16 instr) {
	switch(i00f0) {
		case 0:		/* nop */
			break;
		case 1:		/* div0u */
			regs.sr &= ~(SR_M_MASK | SR_Q_MASK | SR_T_MASK);
			break;
		case 2:	{	/* movt <REG_N> */
			regs.r[i0f00] = regs.sr & SR_T_MASK;
			break;
		}
		default:
			return sim_exec_unimpl(instr);
	}
	sim_next_pc();
	return SIME_OK;
}

/* sts CR,<REG_N> */
int exec_000a(uint16 instr) {
	uint32 sgr;
	uint32* srcregs[16] = {
		&regs.mach, &regs.macl, &regs.pr, &sgr, NULL,
		&regs.fpul, &regs.fpscr, NULL, NULL, NULL, NULL,
		NULL, NULL, NULL, NULL, &regs.dbr
	};
	int regidx = i0f00;
	int srcregidx = i00f0;
	if (srcregidx == 3)
		DEBUG("writing to weird reg SGR\n",0);
	regs.r[regidx] = *(srcregs[srcregidx]);
	sim_next_pc();
	return SIME_OK;
}

/* rte/rts */
int exec_000b(uint16 instr) {
	if (i00f0 == 1) {	/* sleep */
		sim_next_pc();
	} else {
		uint32 dpc = regs.pc + 2;
		if (i00f0 == 2) {	/* rte */
			regs.npc = regs.spc;
			regs.sr = regs.ssr;
		} else {		/* rts */
			regs.npc = regs.pr;
		}
		sim_exec_delay(dpc);
	}
	return SIME_OK;
}

/* mov.b @(R0,<REG_M>),<REG_N> */
int exec_000c(uint16 instr) {
	uint32 ea = regs.r[0] + regs.r[i00f0];
	sim_next_pc();
	sim_read_and_check(ea, 1, (uint8*)&regs.r[i0f00]);
	sim_sign_extend_byte(&regs.r[i0f00]);
	return SIME_OK;
}

/* mov.w @(R0,<REG_M>),<REG_N> */
int exec_000d(uint16 instr) {
	uint32 ea = regs.r[0] + regs.r[i0f00];
	sim_next_pc();
	sim_read_and_check(ea, 2, (uint8*)&regs.r[i00f0]);
	sim_sign_extend_word(&regs.r[i00f0]);
	return SIME_OK;
}

/* mov.l @(R0,<REG_M>),<REG_N> */
int exec_000e(uint16 instr) {
	uint32 ea = regs.r[0] + regs.r[i0f00];
	sim_next_pc();
	return sim_read(ea, 4, (uint8*)&regs.r[i00f0]);
}

/* 0000nnnnmmmm1111 mac.l @<REG_M>+,@<REG_N>+     */
int exec_000f(uint16 instr) {
	uint32 op1, op2;
	uint64 result;

	sim_read_and_check(regs.r[i0f00], 4, (uint8*)&op2); regs.r[i0f00] += 4;
	sim_read_and_check(regs.r[i00f0], 4, (uint8*)&op1); regs.r[i00f0] += 4;
	
	result = (uint64)op1 * (uint64)op2;
	result += regs_mac;
	regs_mac_set(result);
	sim_next_pc();
	return SIME_OK;
}


sim_func funcs_0000[] = {
	sim_exec_unimpl,
	sim_exec_unimpl,
	exec_0002,
	exec_0003,
	exec_0004,
	exec_0005,
	exec_0006,
	exec_0007,
	exec_0008,
	exec_0009,
	exec_000a,
	exec_000b,
	exec_000c,
	exec_000d,
	exec_000e,
	exec_000f
};

int sim_exec_0000(uint16 instr) {
	sim_func func = funcs_0000[i000f];
	return func(instr);
}
