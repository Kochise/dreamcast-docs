/* Opcodes Fxxx are all floating point -- we don't support those yet

   Output from GDB's 'gencode -t'

1111nnnnmmmm0000 fadd <FREG_M>,<FREG_N>        
1111nnnnmmmm0001 fsub <FREG_M>,<FREG_N>        
1111nnnnmmmm0010 fmul <FREG_M>,<FREG_N>        
1111nnnnmmmm0011 fdiv <FREG_M>,<FREG_N>        
1111nnnnmmmm0100 fcmp/eq <FREG_M>,<FREG_N>     
1111nnnnmmmm0101 fcmp/gt <FREG_M>,<FREG_N>     
1111nnnnmmmm0110 fmov.s @(R0,<REG_M>),<FREG_N> 
1111nnnnmmmm0111 fmov.s <FREG_M>,@(R0,<REG_N>) 
1111nnnnmmmm1000 fmov.s @<REG_M>,<FREG_N>      
1111nnnnmmmm1001 fmov.s @<REG_M>+,<FREG_N>     
1111nnnnmmmm1010 fmov.s <FREG_M>,@<REG_N>      
1111nnnnmmmm1011 fmov.s <FREG_M>,@-<REG_N>     
1111nnnnmmmm1100 fmov <FREG_M>,<FREG_N>        
1111nnnn01011101 fabs <FREG_N>                 
1111nnnn10111101 fcnvds <DR_N>,FPUL            
1111nnnn10101101 fcnvsd FPUL,<DR_N>            
1111nnmm11101101 fipr <FV_M>,<FV_N>            
1111nnnn10001101 fldi0 <FREG_N>                
1111nnnn10011101 fldi1 <FREG_N>                
1111nnnn00011101 flds <FREG_N>,FPUL            
1111nnnn00101101 float FPUL,<FREG_N>           
1111nnnn01001101 fneg <FREG_N>                 
1111101111111101 frchg                         
1111001111111101 fschg                         
1111nnnn01101101 fsqrt <FREG_N>                
1111nnnn00111101 ftrc <FREG_N>, FPUL           
1111nnnn00001101 fsts FPUL,<FREG_N>            
1111nnnnmmmm1110 fmac <FREG_0>,<FREG_M>,<FREG_N>


*/

#include "sh4sim.h"


/* 1111nnnnmmmm1001 fmov.s @<REG_M>+,<FREG_N> */
/* SZ==0: move 4 bytes into an fr reg
   SZ==1: move 8 bytes into a dr reg */
int exec_f009(uint16 instr) {
	if (regs.fpscr & FPSCR_SZ_MASK) {
		regs.r[i00f0] += 8;
	} else {
		regs.r[i00f0] += 4;
	}
	sim_next_pc();
	return SIME_OK;
}

int exec_fnop(uint16 instr) {
	sim_next_pc();
	return SIME_OK;
}

sim_func funcs_f000[] = {
	exec_fnop,
	exec_fnop,
	exec_fnop,
	exec_fnop,
	exec_fnop,
	exec_fnop,
	exec_fnop,
	exec_fnop,
	exec_fnop,
	exec_f009,
	exec_fnop,
	exec_fnop,
	exec_fnop,
	exec_fnop,
	exec_fnop,
	exec_fnop
};

int sim_exec_f000(uint16 instr) {
	sim_func func = funcs_f000[i000f];
	return func(instr);
}

