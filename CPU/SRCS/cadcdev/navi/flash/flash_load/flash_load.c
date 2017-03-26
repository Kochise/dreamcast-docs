/*
   flash_load.c
   (c)2002 Dan Potter
*/

/* This program takes whatever is in /rd/flash.bin and loads it into
   the flash chip where the bootstrap is expecting it. It will be
   loaded at 8c010000 and executed on power-up. Note that this only
   erases as much flash as is necessary to load the program. This
   program requires a "navi" subarch build of KOS. */

#include <kos.h>
#include <assert.h>
#include <navi/flash.h>

extern uint8 romdisk[];
KOS_INIT_ROMDISK(romdisk);

int main(int argc, char **argv) {
	cont_btn_callback(0, CONT_START, (cont_btn_callback_t)arch_exit);
	file_t f;
	void * ptr;
	uint32 len;
	uint32 erase_blocks[] = { 0x4000, 0x6000, 0x8000, 0x10000,
		0x20000, 0x30000, 0x40000, 0x50000, 0x60000,
		0x70000, 0x80000, 0x90000, 0xA0000, 0xB0000,
		0xC0000, 0xD0000, 0xE0000, 0xF0000, 0 };
	int	i;
	

	if (nvflash_detect() < 0) {
		printf("Couldn't detect the flash. Did you switch over?\n");
		return 0;
	}

	f = fs_open("/rd/flash.bin", O_RDONLY);
	if (!f) {
		printf("Couldn't open /rd/flash.bin\n");
		return 0;
	}
	ptr = fs_mmap(f); assert(ptr);
	len = fs_total(f);

	printf("Erasing old program (if any)...\n");
	for (i=0; erase_blocks[i]; i++) {
		if (erase_blocks[i] >= (len+0x4000))
			break;
		printf("  erasing block @ %08x\n", erase_blocks[i]);
		if (nvflash_erase_block(erase_blocks[i]) < 0) {
			printf("    failed!\n");
			return 0;
		}
	}

	printf("Loading /rd/flash.bin (len %d) into the flash...\n", len);
	if (nvflash_write_block(0x4000, ptr, len) < 0) {
		printf("Couldn't write the flash\n");
		return 0;
	}

	printf("Flash written successfully\n");

	return 0;
}


