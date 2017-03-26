/* KallistiOS ##version##

   startnet.c
   Copyright (C)2003 Dan Potter
*/

/*

This program takes care of the complete task of starting up networking in
a user-friendly way. If no network config is present, it runs the network
configurator to create one. It then starts the requested driver and lwIP
itself.

*/

#include <sys/process.h>
#include <kos/netcfg.h>
#include <stdio.h>

netcfg_t cfg;
	
int spawn(const char * prog) {
	kprocess_t * p;

	p = process_vfork();
	if (!p) {
		perror("can't vfork");
		return -1;
	}

	if (process_execv(prog, 0, NULL) < 0) {
		perror("can't execv");
		return -1;
	}

	return process_wait(p);
}

int runcfg() {
	if (spawn("netcfg.elf") < 0) {
		printf("startnet: can't run netcfg, giving up\n");
		return -1;
	} else
		return 0;
}

int rundrv() {
	char b[64];
	sprintf(b, "net_%s.elf", cfg.driver);
	
	if (spawn(b) < 0) {
		printf("startnet: can't run driver '%s', giving up\n", b);
		return -1;
	} else
		return 0;
}

int runlwip() {
	if (spawn("net_lwip.elf") < 0) {
		printf("startnet: can't run net_lwip, giving up\n");
		return -1;
	} else
		return 0;
}

int main(int argc, char **argv) {
	printf("startnet: starting network servers\n");
	while (netcfg_load(&cfg) < 0) {
		printf("startnet: no config! running netcfg\n");
		if (runcfg() < 0)
			return -1;
	}

	printf("startnet: got a valid config\n");

	if (rundrv() < 0)
		return -1;
	if (runlwip() < 0)
		return -1;

	printf("startnet: done\n");
	return 0;
}
