/* Opcodes cxxx -- bit operations, trap, and *gasp* more mov's

   Output from GDB's 'gencode -t': (and moved around my jrd)

11000000i8*1.... mov.b R0,@(<disp>,GBR)        // implemented (jrd)
11000001i8*2.... mov.w R0,@(<disp>,GBR)        // implemented (jrd)
11000010i8*4.... mov.l R0,@(<disp>,GBR)        // implemented (jrd)
11000011i8*1.... trapa #<imm>                  // implemented (sort of)
11000100i8*1.... mov.b @(<disp>,GBR),R0        // implemented (jrd)
11000101i8*2.... mov.w @(<disp>,GBR),R0        // implemented (jrd)
11000110i8*4.... mov.l @(<disp>,GBR),R0        // implemented (jrd)
11000111i8p4.... mova @(<disp>,PC),R0          // implemented (jrd)
11001000i8*1.... tst #<imm>,R0                 // implemented (jrd)
11001001i8*1.... and #<imm>,R0                 // implemented (jrd)
11001010i8*1.... xor #<imm>,R0                 // implemented (jrd)
11001011i8*1.... or #<imm>,R0                  // implemented (jrd)
11001100i8*1.... tst.b #<imm>,@(R0,GBR)        // implemented (jrd)
11001101i8*1.... and.b #<imm>,@(R0,GBR)        // implemented (jrd)
11001110i8*1.... xor.b #<imm>,@(R0,GBR)        // implemented (jrd)
11001111i8*1.... or.b #<imm>,@(R0,GBR)         // implemented (jrd)

*/

#include "sh4sim.h"

/* mov.b R0,@(<disp>,GBR) */
int exec_c000(uint16 instr) {
	uint32 disp = instr & 0x00ff;
	int ea = regs.gbr + disp;
	sim_write(ea, 1, (uint8*)&regs.r[0]);
	sim_next_pc();
	return SIME_OK;
}

/* mov.w R0,@(<disp>,GBR) */
int exec_c100(uint16 instr) {
	uint32 disp = instr & 0x00ff;
	int ea = regs.gbr + disp * 2;
	sim_write(ea, 2, (uint8*)&regs.r[0]);	
	sim_next_pc();
	return SIME_OK;
}

/* mov.l R0,@(<disp>,GBR) */
int exec_c200(uint16 instr) {
	uint32 disp = instr & 0x00ff;
	int ea = regs.gbr + disp * 4;
	sim_write(ea, 4, (uint8*)&regs.r[0]);	
	sim_next_pc();
	return SIME_OK;
}

/* trapa #<imm> */
int exec_c300(uint16 instr) {
	int code = instr & 0x00ff;
	DEBUG("trapa #%x\n", code);
	sim_next_pc();
	if (code == 0)
		return SIME_ERROR;
	else
		return SIME_OK;
}

/* mov.b @(<disp>,GBR),R0 */
int exec_c400(uint16 instr) {
	uint32 disp = instr & 0x00ff;
	int ea = regs.gbr + disp;
	sim_read(ea, 1, (uint8*)&regs.r[0]);
	sim_sign_extend_byte(&regs.r[0]);
	sim_next_pc();
	return SIME_OK;
}

/* mov.w @(<disp>,GBR),R0 */
int exec_c500(uint16 instr) {
	uint32 disp = instr & 0x00ff;
	int ea = regs.gbr + disp * 2;
	sim_read(ea, 2, (uint8*)&regs.r[0]);
	sim_sign_extend_word(&regs.r[0]);
	sim_next_pc();
	return SIME_OK;
}

/* mov.l @(<disp>,GBR),R0 */
int exec_c600(uint16 instr) {
	uint32 disp = instr & 0x00ff;
	int ea = regs.gbr + disp * 4;
	sim_read(ea, 4, (uint8*)&regs.r[0]);
	sim_next_pc();
	return SIME_OK;
}

/* mova @(<disp>,PC),R0 */
int exec_c700(uint16 instr) {
	uint32 disp = instr & 0x00ff;
	uint32 ea = 4 + (regs.pc & 0xfffffffc) + disp * 4;
	regs.r[0] = ea;
	sim_next_pc();
	return SIME_OK;
}

/* tst #<imm>,R0 */
int exec_c800(uint16 instr) {
	uint32 imm = instr & 0x00ff;
	if (regs.r[0] & imm)
		regs.sr &= ~SR_T_MASK;
	else
		regs.sr |= SR_T_MASK;
	sim_next_pc();
	return SIME_OK;
}

/* and #<imm>,R0 */
int exec_c900(uint16 instr) {
	uint32 imm = instr & 0x00ff;
	regs.r[0] = regs.r[0] & imm;
	sim_next_pc();
	return SIME_OK;
}

/* xor #<imm>,R0 */
int exec_ca00(uint16 instr) {
	uint32 imm = instr & 0x00ff;
	regs.r[0] ^= imm;
	sim_next_pc();
	return SIME_OK;
}

/* or #<imm>,R0 */
int exec_cb00(uint16 instr) {
	uint32 imm = instr & 0x00ff;
	regs.r[0] |= imm;
	sim_next_pc();
	return SIME_OK;
}

/* tst.b #<imm>,@(R0,GBR) */
int exec_cc00(uint16 instr) {
	uint32 imm = instr & 0x00ff;
	if ((regs.r[0] + regs.gbr) & imm)
		regs.sr &= ~SR_T_MASK;
	else	
		regs.sr |= SR_T_MASK;
		
	sim_next_pc();
	return SIME_OK;
}

/* and.b #<imm>,@(R0,GBR) */
int exec_cd00(uint16 instr) {
	uint32 imm = instr & 0x00ff;
	uint32 tmp;
	uint32 ea = regs.r[0] + regs.gbr;
	
	sim_read(ea, 1, (uint8*)tmp);
	tmp &= imm;
	sim_write(ea, 1, (uint8*)tmp);
	
	sim_next_pc();
	return SIME_OK;
}

/* xor.b #<imm>,@(R0,GBR) */
int exec_ce00(uint16 instr) {
	uint32 imm = instr & 0x00ff;
	uint32 tmp;
	uint32 ea = regs.r[0] + regs.gbr;
	
	sim_read(ea, 1, (uint8*)tmp);
	tmp ^= imm;
	sim_write(ea, 1, (uint8*)tmp);
	
	sim_next_pc();
	return SIME_OK;
}

/* or.b #<imm>,@(R0,GBR) */
int exec_cf00(uint16 instr) {
	uint32 imm = instr & 0x00ff;
	uint32 tmp;
	uint32 ea = regs.r[0] + regs.gbr;
	
	sim_read(ea, 1, (uint8*)tmp);
	tmp |= imm;
	sim_write(ea, 1, (uint8*)tmp);
	
	sim_next_pc();
	return SIME_OK;
}

sim_func funcs_c000[] = {
	exec_c000,
	exec_c100,
	exec_c200,
	exec_c300,
	exec_c400,
	exec_c500,
	exec_c600,
	exec_c700,
	exec_c800,
	exec_c900,
	exec_ca00,
	exec_cb00,
	exec_cc00,
	exec_cd00,
	exec_ce00,
	exec_cf00
};

int sim_exec_c000(uint16 instr) {
	sim_func func = funcs_c000[i0f00];
	return func(instr);
}
