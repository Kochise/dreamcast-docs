#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include "sh4sim.h"
#include "serial.h"

/********************************************************************/
/* Define the following if you want to enable the full spiel (connect to
   remote host and enable remote register read/write) */
#define FULL_MONTY

/* The "Dreamcast" ROM. In reality this is a loaded copy of a ROM file
   from a disk file for the emulated SH4 to play with. Write requests
   to this region will fail. */
uint8* dc_rom = NULL;

/* The "Dreamcast" RAM -- in reality this is a scratch buffer for
   the RAM the emulated SH4 will use, and all requests outside this
   buffer (or its equivalent) will go to the real Dreamcast. */
uint8* dc_ram = NULL;

#if 0
/* A small test program to copy into "RAM" */
uint16	instrwords[] = {
	0xd003,		/* mov.l pc+0x10, r0 */
	0xe1ff,		/* mov #-1,r1 */
	0x2012,		/* mov.l r1,@r0 */
	0xc300,		/* trap #0 */
	0x0009,		/* nop */
	0x0009,		/* nop */
	0x0009,		/* nop */
	0x0009,		/* nop */
	0x8040,		/* border reg address */
	0xa05f
};
#endif
uint16 instrwords[] = {
	0xe004,		/* mov #4,r0 */
	0x6008,		/* swap.b r0, r0 */
	0x0009
};

/* File to output debug messages to */
FILE *debug_log = NULL;

/********************************************************************/
#define RAM_RDONLY	0
#define RAM_RDWR	1
struct region_t {
	uint32		base;		/* SH4 base */
	uint32		size;		/* Segment size */
	uint8*		src;		/* Memory source (if any) */
	int		flags;		/* Flags */
	
	struct region_t*	next;
};

struct region_t *regions = NULL;

void add_region(uint32 base, int size, uint8* src, int flags) {
	struct region_t* r;
	if (regions == NULL) {
		r = regions = malloc(sizeof(struct region_t));
		r->next = NULL;
	}
	else {
		r = malloc(sizeof(struct region_t));
		r->next = regions;
		regions = r;
	}
	
	r->base = base;
	r->size = size;
	r->src = src;
	r->flags = flags;
}

struct region_t* find_region(uint32 addr) {
	struct region_t * r = regions;
	while (r != NULL) {
		if (r->base <= addr && addr < (r->base+r->size))
			return r;
		r = r->next;
	}
	return NULL;
}

void init_regions() {
	/* Pass through an CPU access that gets through the sim */
	add_region(0x1f000000, 16*1024*1024, NULL, RAM_RDWR);

	/* Area 0: Boot ROM */
	add_region(0x00000000, 2*1024*1024, dc_rom, RAM_RDONLY);

	/* Use these lines for Area 0/3 if you want to play with
	   the real Dreamcast ROM/RAM */
	//add_region(0x00000000, 2*1024*1024, NULL, RAM_RDONLY);
	//add_region(0x0c000000, 0x00010000, NULL, RAM_RDWR);
	
	/* Area 0: Flash ROM */
	add_region(0x00200000, 256*1024, NULL, RAM_RDONLY);
	
	/* Area 0: Dreamcast external registers */
	add_region(0x00240000, 0x3cd0000, NULL, RAM_RDWR);
	
	/* Area 5: Expansion port */
	add_region(0x14000000, 64*1024*1024, NULL, RAM_RDWR);

	/* Area 1: Video RAM */
	add_region(0x05000000, 8*1024*1024, NULL, RAM_RDWR);
	
	/* Area 3: "RAM" */
	add_region(0x0c000000, 16*1024*1024, dc_ram, RAM_RDWR);
}

int ice_read(uint32 addr, uint32 len, uint8* buffer) {
	uint32 realaddr;
	struct region_t *reg;
	
	/* Pull out the cache bits -- we don't care */
	realaddr = (addr & (~0xe0000000));

	// printf("ice_read: reading address %08x(%08x), len %d\n", addr, realaddr, len);
	
	reg = find_region(realaddr);
	if (reg == NULL) {
		DEBUG("%08x is an invalid address\n", addr);
		return SIME_ERROR;
	}
	
	if (reg->src != NULL) {
		memcpy(buffer, reg->src + realaddr - reg->base, len);
	} else {
		if (addr < 0xa0800000 || addr >= 0xa09fffff)
			DEBUG("attempt to read from outside-ram location %08x, pc==%08x\n", addr, regs.pc);
#ifdef FULL_MONTY
		sc_read_memory(addr, len, (char*)buffer);
#endif
	}
	return SIME_OK;
}

int ice_write(uint32 addr, uint32 len, uint8* buffer) {
	uint32 realaddr;
	struct region_t *reg;
	
	/* Pull out cache bits -- we don't care */
	realaddr = (addr & (~0xe0000000));
	
	// printf("ice_write: writing address %08x(%08x), len %d\n", addr, realaddr, len);
	
	reg = find_region(realaddr);
	if (reg == NULL) {
		DEBUG("%08x is an invalid address\n", addr);
		return SIME_ERROR;
	}

	if (reg->flags & RAM_RDONLY) {
		DEBUG("ignoring write to unwritable region %08x - %08x\n",
			reg->base, reg->base+reg->size-1);
		return SIME_OK;
	}
	
	if (reg->src != NULL) {
		memcpy(reg->src + realaddr - reg->base, buffer, len);
	} else {
		if (addr < 0xa0800000 || addr >= 0xa09fffff)
			DEBUG("attempt to write to outside-ram location %08x, pc=%08x\n", addr, regs.pc);
#ifdef FULL_MONTY
		sc_write_memory(addr, len, (char*)buffer);
#endif
	}
	return SIME_OK;
}

/********************************************************************/
int load_rom() {
	FILE *f;
	
	/* Load the ROM into its own region */
	dc_rom = malloc(2048 * 1024);
	f = fopen("rom.bin", "r");
	if (!f) {
		printf("Can't load rom image rom.bin!\n");
		memset(dc_rom, 0, 2048*1024);
		return -1;
	}
	
	fread(dc_rom, 2048*1024, 1, f);
	fclose(f);
	
	/* Also do what the ROM does on startup and make a
	   copy of the first parts into RAM */
	memcpy(dc_ram, dc_rom, 0x0007ffc0);
	
	return 0;
}

void load_program() {
	FILE *f = fopen("prog.bin", "r");
	int t;
	fseek(f, 0, SEEK_END); t=ftell(f); fseek(f, 0, SEEK_SET);
	fread(dc_ram + 0x00010000, t, 1, f);
	fclose(f);
}

void start_log(char *fn) {
	debug_log = fopen(fn, "a+");
	fprintf(debug_log, "------------- Starting new debug session --------------\n");
}

int main(int argc, char **argv) {
	int rv;

	/* Start the log file */
	start_log("debug.log");

	/* Initialize the "Dreamcast" */
	dc_ram = (uint8*)malloc(16 * 1024 * 1024);
	memset(dc_ram, 0, 16*1024*1024);
	load_program();
	load_rom();
	init_regions();

#ifdef FULL_MONTY
	/* If we're doing it all, bring up the serial interface */
	if (ser_init("/dev/ttyS0", 57600)) {
		printf("Serial couldn't initialize.. giving up\n");
		return -1;
	}
#endif
	
	/* Initialize the simulator */
	if (sim_init(ice_read, ice_write) != SIME_OK) {
		printf("Simulator init returned not OK\n");
		return -1;
	}
	
	/* Bring up the interface */
	regs.pc = regs.npc = 0x8c010000;
	disasm_init();
	screen_init();

#ifdef FULL_MONTY
	sc_connect_to_remote();
	DEBUG("Connected to remote host\n",0);
#endif

	/* Run the program */
	codewnd_draw();
	regswnd_draw();
	msgswnd_draw();
	screen_run();
	screen_shutdown();
	
	/* Free up resources */
	free(dc_ram);
	free(dc_rom);

#ifdef FULL_MONTY
	/* Close the serial port */
	ser_close();
#endif
}




