#include <stdio.h>
#include "sh4sim.h"


void sim_register_dump() {
	int i;
	
	printf("R0-R7: ");
	for (i=0; i<8; i++)
		printf("%08x  ", regs.r[i]);
	printf("\nR8-R15:");
	for (i=8; i<16; i++)
		printf("%08x  ", regs.r[i]);
	printf("\nPC: %08x   SR: %08x   PR: %08x\n", regs.pc, regs.sr, regs.pr);
}

