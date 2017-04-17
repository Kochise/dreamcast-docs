#include "terminal.h"
#include "sio.h"


// SPU DMA
// by bITmASTER (bITmASTER@bigfoot.com)

void printf (char *fmt, ...);

char buffer[1024] __attribute__ ((aligned(32)));


typedef unsigned int UINT;


typedef struct {
	UINT ext_addr;			//  external address (SPU-RAM or parallel port)
	UINT cpu_addr;			//  CPU address
	UINT size;				//  size in bytes, all addr & size must be mod 32 !!!
	UINT dir;				//  0: cpu->ext, 1: ext->cpu
	UINT mode;				//  5 for SPU transfer
	UINT ctrl1;				//  b0
	UINT ctrl2;				//  b0
	UINT u1;				//  ??
} DMA;

typedef struct {
	UINT ext_addr;			
	UINT cpu_addr;
	UINT size;
	UINT status;
} EXTDMASTAT;

typedef struct {
	DMA dma[4];
	UINT u1[4];				// function unknown
	UINT wait_state;
	UINT u2[10];			// function unknown
	UINT magic;			
	EXTDMASTAT extdmastat[4];
} EXTDMAREGISTER;

	


void main2( void )
{
	volatile int *spu_ram = (int *)0xa0800000;
	volatile int *xxy = (int *) 0xa05f6884;
	volatile int *qacr = (int *) 0xff000038;
	volatile int *shdma = (int *)	0xFFA00000;
	volatile EXTDMAREGISTER *extdmareg = (EXTDMAREGISTER *) 0xa05f7800;
	
	int i;
	int chn = 0;									// 0: SPU; 1,2,3 for ext (parallel port)
	int dest;


	dest = 0xa0800000;								// SPU memory

	extdmareg->wait_state = 0x0;					// wait states (for non-dma access)
	extdmareg->magic = 0x4659404f;					// magic number for release the ext DMA

	for ( i = 0; i < 64; i++ )						// fill SPU RAM
		spu_ram[i] = 0x12345678;

	for ( i = 0; i < 1024; i++ )					// test pattern
		buffer[i] = i;
	printf( "buffer: %p\n", buffer );

// yeah, the extern dma is a very complex thing
// it uses the sh dma with On-demand data transfer mode (DDT mode)


	shdma[0x20/4] = 0;				// SAR2 = 0
	shdma[0x24/4] = 0;				// DAR2 = 0
	shdma[0x28/4] = 0;				// DMATCR2 = 0
	shdma[0x2c/4] = 0x12c0;			// CHCR2 = 0x12c0, 32-byte block transfer, burst mode, External request, single address mode, Source address incremented
	shdma[0x40/4] = 0x8201;			// DMAOR = 0x8201, 0—DMAC Master Enable, CH2 > CH0 > CH1 > CH3, On-Demand Data Transfer
	*xxy = 0;

	qacr[0] = 0x10;
	qacr[1] = 0x10;


// reset all dma channels

	for ( i = 0; i < 4; i++ ) {
		extdmareg->dma[i].ctrl1 = 0;
		extdmareg->dma[i].ext_addr = 0;
		extdmareg->dma[i].cpu_addr = 0;			
		extdmareg->dma[i].size = 0;
		extdmareg->dma[i].dir = 0;
		extdmareg->dma[i].mode = 0;
		extdmareg->dma[i].ctrl1 = 0;
		extdmareg->dma[i].ctrl2 = 0;	
	}
		
	 


// start dma	
// dont forget flush cache before start dma

	extdmareg->dma[chn].ctrl1 = 0;
	extdmareg->dma[chn].ctrl2 = 0;
	extdmareg->dma[chn].ext_addr = dest & 0x1fffffe0;
	extdmareg->dma[chn].cpu_addr = (int) buffer & 0x1fffffe0;			
	extdmareg->dma[chn].size = 64 | 0x80000000;
	extdmareg->dma[chn].dir = 0;
	extdmareg->dma[chn].mode = 5;							// SPU: 5, ext: 0
	extdmareg->dma[chn].ctrl1 = 1;
	extdmareg->dma[chn].ctrl2 = 1;			


	terminal();								// yep, this is my terminal hexdump

}
