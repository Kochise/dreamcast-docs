/* test.c - test prg */

#include "../src/types.h"
#include "../src/sh4/dxm.h"

#define DRIVERSIZE 16000
#define MODULESIZE 2000000

extern void *driver;
extern void *module;

extern void __exit(sint32);

/* keep gcc from whining */
void
exit(status)
	sint32 status;
{
	__exit(status);
}

int
main()
{

/* 	printf("disabling the ARM\n");	*/
	dxm_disable_arm();

/*	printf("loading module\n"); */
	/* load module */
	dxm_sramcpy4((void *)0x00010000, &module, MODULESIZE);

/* 	printf("loading driver\n"); */
	/* load driver */
	dxm_load_driver(&driver, DRIVERSIZE);

/* 	printf("enabling the ARM\n"); */
	dxm_enable_arm();

	/* wait for ARM to initialize */
	if (dxm_init_done() < 0) {
/* 		printf("timeout!\n"); */
		exit(0);
	}

	/* set mono */
	dxm_set_stereo(FALSE);

/* 	printf("start playing the XM\n"); */
	dxm_play_xm();

/* 	printf("all done!\n"); */

	return (0);

}
