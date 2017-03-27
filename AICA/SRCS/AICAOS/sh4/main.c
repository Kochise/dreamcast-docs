
#include <kos.h>

#include "../aica_common.h"
#include "aica_sh4.h"

extern uint8 romdisk[];

KOS_INIT_FLAGS(INIT_DEFAULT | INIT_MALLOCSTATS);

KOS_INIT_ROMDISK(romdisk);

/* Wrapper to the real function. */
static AICA_SHARED(sh4_puts)
{
	return puts((char *)in);
}

AICA_SHARED_LIST = {
	AICA_SHARED_LIST_ELEMENT(sh4_puts, 0x100, 0),
	AICA_SHARED_LIST_END,
};

AICA_ADD_REMOTE(arm_test, PRIORITY_DEFAULT);

static volatile int done = 0;

static void * exit_thd(void *param)
{
	sleep(5);
	done = 1;
	return NULL;
}

int main(int argc, char **argv)
{
	thd_create(THD_DEFAULTS, exit_thd, NULL);

	int ret = aica_init("/rd/aicaos.drv");
	if (ret) {
		printf("Error %i.\n", ret);
		return ret;
	}
	
	printf("SH4: My job\'s complete.\n");
	while (!done) {
		arm_test(NULL, NULL);
		usleep(5000);
	}

	aica_exit();
	return 0;
}

