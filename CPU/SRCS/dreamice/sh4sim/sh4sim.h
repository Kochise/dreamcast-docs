#ifndef __SH4SIM_H
#define __SH4SIM_H

#include <string.h>

/* Change these if neccessary for your platform */
typedef unsigned short uint16;
typedef unsigned char uint8;
typedef unsigned long uint32;
typedef unsigned long long uint64;

typedef short int16;
typedef char int8;
typedef long int32;
typedef long long int64;

/* Memory Callback type */
typedef int (*mem_callback_t)(uint32 address, uint32 len, uint8* buffer);

/* Register state definitions */
typedef struct {
	uint32		r[16];		/* 16 general registers */
	uint32		pc, pr;		/* Prg Counter and Prg Return */
	uint32		gbr, vbr, dbr;	/* Global, Vector, and Debug base */
	uint32		mach, macl;	/* Mult Accum high and low */
	uint32		sr;		/* Status */
	uint32		fpul;		/* Floating point communication */
	uint32		fpscr;		/* Floating Point status & control */
	
	union fregs_u {			/* Floating point regs */
		float	f[16];
		double	d[8];
		uint32	i[16];
	} fregs[2];
	
	uint32		ssr, spc;	/* Saved PC and SR */
	uint32		rbanks[2][8];	/* Extra register banks */
	uint32*		rbank;		/* Pointer to current register bank */
	
	uint32		npc;		/* Next PC (deals with delayed branch) */
	
	/* The rest are random memory-mapped system registers, most of which
	   we will keep around so that programs that poke at them will get
	   the right values. */
	/* CCN registers */
	uint32		pteh, ptel, ttb, tea, mmucr, basra, basrb,
			ccr, tra, expevt, intevt, ptea, qacr0, qacr1;
	/* UBC registers */
	uint32		bara, bamra, bbra, barb, bamrb, bbrb, bdrb, bdmrb, brcr;
	/* BSC registers */
	uint32		bcr1, bcr2, wcr1, wcr2, wcr3, mcr, pcr, rtcsr, rtcnt,
			rtcor, rfcr, pctra, pdtra, pctrb, pdtrb, gpioic, sdmr2, sdmr3;
	/* DMAC regsisters */
	uint32		sar0, dar0, dmatcr0, chcr0, sar1, dar1, dmatcr1, chcr1,
			sar2, dar2, dmatcr2, chcr2, sar3, dar3, dmatcr3, chcr3,
			dmaor;
	/* CPG registers */
	uint32		frqcr, stbcr, wtcnt, wtcsr, stbcr2;
	/* RTC registers */
	uint32		r64cnt, rseccnt, rmincnt, rhrcnt, rwkcnt, rdavcnt, rmoncnt,
			rvrcnt, rsecar, rminar, rhrar, rwkar, rdavar, rmonar, rcr1, rcr2;
	/* INTC registers */
	uint32		icr, ipra, iprb, iprc;
	/* TMU registers */
	uint32		tocr, tstr, tcor0, tcnt0, tcr0, tcor1, tcnt1, tcr1,
			tcor2, tcnt2, tcr2, tcpr2;
	/* SCI registers */
	/* SCIF registers */
} sh4regs_t;

/* SR constants */
#define SR_MD_MASK	(1 << 30)
#define SR_RB_MASK	(1 << 29)
#define SR_BL_MASK	(1 << 28)
#define SR_M_MASK	(1 << 9)
#define SR_Q_MASK	(1 << 8)
#define SR_I_MASK	(0xf << 4)
#define SR_S_MASK	(1 << 1)
#define SR_T_MASK	(1 << 0)

/* FPSCR constants */
#define FPSCR_FR_MASK	(1 << 21)
#define FPSCR_SZ_MASK	(1 << 20)
#define FPSCR_PR_MASK	(1 << 19)

/* Error codes */
#define SIME_ERROR	-1
#define SIME_OK		0

/* Breakpoint constants */
#define MAX_BREAKPOINTS	32

/* The value to use for "none" in address operations */
#define ADDR_NONE	((uint32)0xffffffff)

/*************************************************** sh4sim.c ***/
/* Global variables */
extern sh4regs_t regs;
extern uint32 breakpoints[MAX_BREAKPOINTS];
extern mem_callback_t	read_mem_callback, write_mem_callback;

/* Simulator memory read/write functions */
int sim_read(uint32 addr, uint32 len, uint8* buffer);
int sim_write(uint32 addr, uint32 len, uint8* buffer);

/* Simulator global functions */
int sim_init(mem_callback_t read, mem_callback_t write);
int sim_execute(uint32 pc);
int sim_step(uint32 pc);

/*************************************************** exec.c *****/
int sim_exec_single();
int sim_exec_delay_real(uint32 dpc);
int sim_exec_unimpl(uint16 instr);
void sim_sign_extend_byte(uint32* l);
void sim_sign_extend_word(uint32* l);

/* A few convienence macros */
#define i000f ((instr & 0x000f))
#define i00f0 ((instr & 0x00f0) >> 4)
#define i0f00 ((instr & 0x0f00) >> 8)
#define if000 ((instr & 0xf000) >> 12)
#define sim_next_pc() regs.npc = regs.pc + 2
#define sim_next_pc_is(v) regs.npc = v
#define sim_exec_delay(dpc) { \
	int rv; \
	if ((rv=sim_exec_delay_real(dpc)) != SIME_OK) \
		return rv; \
}
#define sim_read_and_check(addr, len, buf) { \
	int rv; \
	if ((rv=sim_read(addr, len, buf)) != SIME_OK) \
		return rv; \
}
#define sim_write_and_check(addr, len, buf) { \
	int rv; \
	if ((rv=sim_write(addr, len, buf)) != SIME_OK) \
		return rv; \
}

#define regs_mac ( (((uint64)regs.mach) << 32) | ((uint64)regs.macl) )
#define regs_mac_set(x) \
	regs.mach = ((x >> 32) & 0xFFFFFFFFL); \
	regs.macl = (x & 0xFFFFFFFFl)

/* Type for instruction handler pointers */
typedef int (*sim_func)(uint16);

/*************************************************** execxxxx.c */
int sim_exec_0000(uint16 instr);
int sim_exec_1000(uint16 instr);
int sim_exec_2000(uint16 instr);
int sim_exec_3000(uint16 instr);
int sim_exec_4000(uint16 instr);
int sim_exec_5000(uint16 instr);
int sim_exec_6000(uint16 instr);
int sim_exec_7000(uint16 instr);
int sim_exec_8000(uint16 instr);
int sim_exec_9000(uint16 instr);
int sim_exec_a000(uint16 instr);
int sim_exec_b000(uint16 instr);
int sim_exec_c000(uint16 instr);
int sim_exec_d000(uint16 instr);
int sim_exec_e000(uint16 instr);
int sim_exec_f000(uint16 instr);

/****************************************************************/
/* A spiffy debug macro */
// #define DEBUG(FMT, args...) printf(__FUNCTION__ ": " FMT, args)
#define DEBUG(FMT, args...) msgswnd_printf(__FUNCTION__ ": " FMT, args)
// #define DEBUG(args...)


#endif	/* __SH4SIM_H */


