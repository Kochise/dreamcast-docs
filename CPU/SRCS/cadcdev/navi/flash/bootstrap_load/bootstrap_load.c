/*
   bootstrap_load.c
   (c)2002 Dan Potter
*/

/* This program will erase the boot block of the flash chip and load
   up /rd/boot.bin into it. You must have physically selected the flash
   chip. This requires a "navi" subarch build of KOS. */

#include <kos.h>
#include <assert.h>
#include <navi/flash.h>

extern uint8 romdisk[];
KOS_INIT_ROMDISK(romdisk);

int main(int argc, char **argv) {
	file_t f;
	void * ptr;
	uint32 len;

	cont_btn_callback(0, CONT_START, (cont_btn_callback_t)arch_exit);
	
	if (nvflash_detect() < 0) {
		printf("Couldn't detect the flash. Did you switch over?\n");
		return 0;
	}

	printf("Erasing boot block...\n");
	if (nvflash_erase_block(0) < 0) {
		printf("Failed!\n");
		return 0;
	}

	f = fs_open("/rd/boot.bin", O_RDONLY);
	if (!f) {
		printf("Couldn't open /rd/boot.bin\n");
		return 0;
	}
	ptr = fs_mmap(f); assert(ptr);
	len = fs_total(f); assert( len == 16384 );

	printf("Loading /rd/boot.bin (len %d) into the flash...\n", len);
	
	if (nvflash_write_block(0, ptr, len) < 0) {
		printf("Couldn't write the flash\n");
		return 0;
	}

	printf("Flash written successfully\n");

	return 0;
}


