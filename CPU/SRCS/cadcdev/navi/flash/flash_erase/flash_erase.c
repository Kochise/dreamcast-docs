/*
   flash_erase.c
   (c)2002 Dan Potter
*/

/* Erases the BIOS flash chip. You must be switched over to the flash
   chip physically. This also requires a "navi" subarch build of KOS. */

#include <kos.h>
#include <assert.h>
#include <navi/flash.h>

extern uint8 romdisk[];
KOS_INIT_ROMDISK(romdisk);

int main(int argc, char **argv) {
	cont_btn_callback(0, CONT_START, (cont_btn_callback_t)arch_exit);

	if (nvflash_detect() < 0) {
		printf("Couldn't detect the flash. Did you switch over?\n");
		return 0;
	}

	printf("Erasing the flash...\n");
	if (nvflash_erase_all() < 0) {
		printf("Couldn't erase the flash\n");
		return 0;
	}

	printf("Flash erased successfully\n");

	return 0;
}


